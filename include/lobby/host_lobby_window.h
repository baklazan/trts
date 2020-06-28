#ifndef TRTS_HOST_SETTINGS_WINDOW_H
#define TRTS_HOST_SETTINGS_WINDOW_H
#include <game_lobby_window.h>
#include <message_reader.h>
#include <message_writer.h>
#include <map>

class HostLobbyWindow : public GameLobbyWindow {
private:
	std::string name_;
	int port_;
	bool created_successfully_;
	int listening_socket_;
	bool AcceptConnection(Glib::IOCondition condition);
	bool ReceiveMessage(int fd, Glib::IOCondition condition);
	void ConnectPlayer(int player_id, int fd);
	void DisconnectPlayer(int fd);
	void FailToCreate(std::string message);
	void StartGame();
	void UpdateReadyStatus();
	std::map<int, int> fd_to_player_;
	std::map<int, MessageReader*> fd_to_reader_;
	std::map<int, MessageWriter*> fd_to_writer_;
	std::map<int, sigc::connection> fd_to_connection_;
	sigc::connection listening_socket_connection_;
public:
	HostLobbyWindow(Glib::RefPtr<Gtk::Application> &app, std::string port_string, std::string name);
	~HostLobbyWindow() override;
	bool CreatedSuccessfully();
};

#endif
