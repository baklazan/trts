#ifndef TRTS_JOIN_LOBBY_WINDOW_H
#define TRTS_JOIN_LOBBY_WINDOW_H
#include <game_lobby_window.h>
#include <message_reader.h>
#include <message_writer.h>

class JoinLobbyWindow : public GameLobbyWindow {
private:
	std::string name_;
	int host_socket_;
	bool created_successfully_;
	void FailToConnect(std::string message);
	bool ReceiveMessage(Glib::IOCondition condition);
	void StartGame();
	MessageReader *message_reader_;
	MessageWriter *message_writer_;
	void RegisterAsPlayer(int player_id);
	sigc::connection io_connection_;
protected:
	virtual void ParseCommand(std::string command) override;
public:
	JoinLobbyWindow(Glib::RefPtr<Gtk::Application> &app, std::string host_port_string, std::string host_ip_string, std::string name);
	~JoinLobbyWindow() override;
	bool CreatedSuccessfully();
};

#endif
