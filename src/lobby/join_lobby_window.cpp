#include <join_lobby_window.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <gtkmm/messagedialog.h>
#include <join_game_window.h>
#include <fcntl.h>
#include <utils.h>
#include <spawn_client.h>
#include <sys/wait.h>

void JoinLobbyWindow::FailToConnect(std::string message) {
	Gtk::MessageDialog message_dialog(message, false, Gtk::MESSAGE_ERROR);
	message_dialog.set_transient_for(*this);
	message_dialog.run();
}

JoinLobbyWindow::JoinLobbyWindow(Glib::RefPtr<Gtk::Application> &app, std::string host_port_string, std::string host_ip_string, std::string name) : GameLobbyWindow(app), message_reader_(nullptr), message_writer_(nullptr), name_(name), host_socket_(-1) {
	created_successfully_ = false;
	
	in_addr ip_address;
	int err = inet_aton(host_ip_string.c_str(), &ip_address);
	if (err == 0) {
		FailToConnect("Invalid IP address");
		return;
	}
	
	char *endptr;
	int host_port = strtol(host_port_string.c_str(), &endptr, 10);
	if (*endptr != '\0') {
		FailToConnect("Invalid port");
		return;
	}
	
	report_error(host_socket_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0));
	sockaddr_in host_address;
	host_address.sin_family = AF_INET;
	host_address.sin_addr = ip_address;
	host_address.sin_port = htons(host_port);
	int res = ::connect(host_socket_, reinterpret_cast<sockaddr*>(&host_address), sizeof(host_address));
	
	if (res < 0) {
		if (errno == EINPROGRESS) {
			fd_set host_fd_set;
			FD_ZERO(&host_fd_set);
			FD_SET(host_socket_, &host_fd_set);
			timeval timeout;
			timeout.tv_sec = 5;
			timeout.tv_usec = 0;
			int selected = select(host_socket_+1, NULL, &host_fd_set, NULL, &timeout);
			if (selected <= 0) {
				FailToConnect("Cannot connect to host");
				return;
			}
			int optval = 0;
			socklen_t optlen = sizeof(optval); 
			report_error(getsockopt(host_socket_, SOL_SOCKET, SO_ERROR, reinterpret_cast<void*>(&optval), &optlen));
			if (optval != 0) {
				FailToConnect("Cannot connect to host");
				return;
			}
		}
		else {
			FailToConnect("Cannot connect to host");
			return;
		}
	}
	
	int flags = fcntl(host_socket_, F_GETFL, NULL);
	report_error(flags);
	flags &= (~O_NONBLOCK);
	report_error(fcntl(host_socket_, F_SETFL, flags));
	
	auto callback = [this](std::string s){ParseCommand(s);};
	message_reader_ = new MessageReader(host_socket_, callback);
	message_writer_ = new MessageWriter(host_socket_);
	
	auto handler = sigc::mem_fun(*this, &JoinLobbyWindow::ReceiveMessage);
	io_connection_ = Glib::signal_io().connect(handler, host_socket_, Glib::IO_IN);
	
	start_button_.set_sensitive(false);
	created_successfully_ = true;
}

bool JoinLobbyWindow::ReceiveMessage(Glib::IOCondition condition) {
	if (message_reader_->Read() == -1) {
		Cancel();
	}
	return true;
}

bool JoinLobbyWindow::CreatedSuccessfully() {
	return created_successfully_;
}

JoinLobbyWindow::~JoinLobbyWindow() {
	if (host_socket_ != -1) {
		report_error(::close(host_socket_));
		io_connection_.disconnect();
	}
	if (message_reader_ != nullptr) {
		delete message_reader_;
	}
	if (message_writer_ != nullptr) {
		delete message_writer_;
	}
}

void JoinLobbyWindow::RegisterAsPlayer(int player_id) {
	player_slots_[player_id]->SetSensitive(true);
	player_slots_[player_id]->SetName(name_);
	player_slots_[player_id]->RegisterObserver(message_writer_);
}

void JoinLobbyWindow::ParseCommand(std::string command) {
	std::istringstream in(command);
	std::string id;
	in >> id;
	if (observing_widgets_.count(id) > 0) {
		observing_widgets_[id]->UpdateState(in);
	}
	else if (id == "player") {
		int player_id;
		in >> player_id;
		RegisterAsPlayer(player_id);
	}
	else if (id == "start") {
		StartGame();
	}
}

void JoinLobbyWindow::StartGame() {
	io_connection_.disconnect();
	int client_pid = SpawnGameClient(host_socket_);
	int status;
	waitpid(client_pid, &status, 0);
	auto handler = sigc::mem_fun(*this, &JoinLobbyWindow::ReceiveMessage);
	io_connection_ = Glib::signal_io().connect(handler, host_socket_, Glib::IO_IN);
}
