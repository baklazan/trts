#include <host_lobby_window.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <utils.h>
#include <spawn_server.h>
#include <spawn_client.h>
#include <game_loop.h>
#include <sys/wait.h>


void HostLobbyWindow::FailToCreate(std::string message) {
	Gtk::MessageDialog message_dialog(message, false, Gtk::MESSAGE_ERROR);
	message_dialog.set_transient_for(*this);
	message_dialog.run();
}


HostLobbyWindow::HostLobbyWindow(Glib::RefPtr<Gtk::Application> &app, std::string port_string, std::string name) : GameLobbyWindow(app), name_(name) {
	created_successfully_ = false;
	
	char *endptr;
	port_ = strtol(port_string.c_str(), &endptr, 10);
	if (*endptr != '\0') {
		FailToCreate("Invalid port");
		return;
	}
	
	player_slots_[0]->SetSensitive(true);
	player_slots_[0]->used_=  true;
	player_slots_[0]->SetName(name_);
	
	listening_socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (listening_socket_ == -1) {
		FailToCreate(strerror(errno));
		return;
	}
	
	sockaddr_in my_address;
	my_address.sin_family = AF_INET;
	my_address.sin_addr.s_addr = INADDR_ANY;
	my_address.sin_port = htons(port_);
	int err = bind(listening_socket_, reinterpret_cast<sockaddr*>(&my_address), sizeof (my_address));
	if (err == -1) {
		FailToCreate(strerror(errno));
		return;
	}
	err = listen(listening_socket_, 16);
	if (err == -1) {
		FailToCreate(strerror(errno));
		return;
	}
	auto connection = Glib::signal_io().connect(sigc::mem_fun(*this, &HostLobbyWindow::AcceptConnection), listening_socket_, Glib::IO_IN);
	listening_socket_connection_ = connection;
	
	for (PlayerSlot *player_slot : player_slots_) {
		auto handler = sigc::mem_fun(*this, &HostLobbyWindow::UpdateReadyStatus);
		player_slot->GetReadyButton()->signal_toggled().connect(handler);
	}
	UpdateReadyStatus();
	start_button_.signal_clicked().connect(sigc::mem_fun(*this, &HostLobbyWindow::StartGame));
	created_successfully_ = true;
}

void HostLobbyWindow::ConnectPlayer(int player_id, int fd) {
	fd_to_player_[fd] = player_id;
	auto callback = [this](std::string s){ParseCommand(s);};
	fd_to_reader_[fd] = new MessageReader(fd, callback);
	MessageWriter *writer = new MessageWriter(fd);
	fd_to_writer_[fd] = writer;
	for (auto it : observed_widgets_) {
		it.second->RegisterObserver(writer);
	}
	player_slots_[player_id]->RemoveObserver(writer);
	player_slots_[player_id]->used_ = true;
	(*writer) << "player " << player_id;
	writer->Flush();
	UpdateReadyStatus();
}

void HostLobbyWindow::DisconnectPlayer(int fd) {
	report_error(::close(fd));
	MessageWriter *writer = fd_to_writer_[fd];
	for (auto it : observed_widgets_) {
		it.second->RemoveObserver(writer);
	}
	delete fd_to_reader_[fd];
	fd_to_reader_.erase(fd);
	delete fd_to_writer_[fd];
	fd_to_writer_.erase(fd);
	player_slots_[fd_to_player_[fd]]->SetDefaults();
	fd_to_player_.erase(fd);
	fd_to_connection_[fd].disconnect();
	fd_to_connection_.erase(fd);
}

bool HostLobbyWindow::AcceptConnection(Glib::IOCondition condition) {
	sockaddr his_address;
	int length = sizeof(his_address);
	int new_socket = accept(listening_socket_, &his_address, reinterpret_cast<socklen_t*> (&length));
	report_error(new_socket);
	
	int player_id = -1;
	for (int i = 0; i < player_slots_.size(); i++) {
		if (!player_slots_[i]->used_) {
			player_id = i;
			break;
		}
	}
	
	if(player_id == -1) {
		report_error(::close(new_socket));
		return true;
	}
	
	ConnectPlayer(player_id, new_socket);
	
	auto handler = sigc::bind<0>(sigc::mem_fun(*this, &HostLobbyWindow::ReceiveMessage), new_socket);
	auto connection = Glib::signal_io().connect(handler, new_socket, Glib::IO_IN);
	fd_to_connection_[new_socket] = connection;
	return true;
}

bool HostLobbyWindow::ReceiveMessage(int fd, Glib::IOCondition condition) {
	if (fd_to_reader_.count(fd) > 0) {
		if (fd_to_reader_[fd]->Read() == -1) {
			DisconnectPlayer(fd);
		}
	}
	else {
		fprintf(stderr, "warning: mesage from unexpected file descriptor\n");
	}
	return true;
}

bool HostLobbyWindow::CreatedSuccessfully() {
	return created_successfully_;
}

HostLobbyWindow::~HostLobbyWindow() {
	for (auto it : fd_to_reader_) {
		delete it.second;
		report_error(::close(it.first));
	}
	for (auto it : fd_to_writer_) {
		delete it.second;
	}
	::close(listening_socket_);
}

void HostLobbyWindow::StartGame() {
	for (const auto &it : fd_to_writer_) {
		(*it.second) << "start";
		it.second->Flush();
	}
	for (auto &it : fd_to_connection_) {
		it.second.disconnect();
	}
	std::pair<int, int> server_io;
	int server_pid = SpawnGameServer(&server_io);
	
	sockaddr_in loopback_address;
	loopback_address.sin_family = AF_INET;
	inet_aton("127.0.0.1", &loopback_address.sin_addr);
	loopback_address.sin_port = htons(port_);
	
	listening_socket_connection_.disconnect();
	int client_pid = SpawnAndConnectGameClient(loopback_address);
	
	sockaddr his_address;
	int length = sizeof(his_address);
	int client_fd = accept(listening_socket_, &his_address, reinterpret_cast<socklen_t*> (&length));
	report_error(client_fd);
	
	std::pair<int, int> client_io(client_fd, client_fd);
	std::vector<std::pair<int, int>> clients_io(1, client_io);
	for (const auto it : fd_to_player_) {
		clients_io.emplace_back(it.first, it.first);
	}
	GameLoop(server_io, clients_io);
	int status;
	waitpid(client_pid, &status, 0);
	waitpid(server_pid, &status, 0);
	
	report_error(::close(client_fd));
	auto handler = sigc::mem_fun(*this, &HostLobbyWindow::AcceptConnection);
	auto connection = Glib::signal_io().connect(handler, listening_socket_, Glib::IO_IN);
	listening_socket_connection_ = connection;
	for (auto it : fd_to_connection_) {
		int fd = it.first;
		auto handler = sigc::bind<0>(sigc::mem_fun(*this, &HostLobbyWindow::ReceiveMessage), fd);
		auto connection = Glib::signal_io().connect(handler, fd, Glib::IO_IN);
		fd_to_connection_[fd] = connection;
	}
}

void HostLobbyWindow::UpdateReadyStatus() {
	bool all_ready = true;
	for (PlayerSlot *player_slot : player_slots_) {
		if (player_slot->used_ && !player_slot->GetReadyButton()->get_active()) {
			all_ready = false;
			break;
		}
	}
	start_button_.set_sensitive(all_ready);
}
