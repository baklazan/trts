#ifndef TRTS_INCLUDE_JOIN_GAME_WINDOW_H
#define TRTS_INCLUDE_JOIN_GAME_WINDOW_H
#include <state_window.h>

class JoinGameWindow : public StateWindow {
private:
	Gtk::Grid layout_grid_;
	Gtk::Button join_button_, cancel_button_;
	Gtk::Entry host_ip_entry_, host_port_entry_, player_name_entry_;
	Gtk::Label host_ip_label_, host_port_label_, player_name_label_;
	void Join();
	void Cancel();
public:
	JoinGameWindow(Glib::RefPtr<Gtk::Application> &app);
	~JoinGameWindow() override;
};

#endif
