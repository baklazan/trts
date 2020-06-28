#ifndef TRTS_HOST_GAME_WINDOW_H
#define TRTS_HOST_GAME_WINDOW_H
#include <state_window.h>

class HostGameWindow : public StateWindow {
private:
	Gtk::Grid layout_grid_;
	Gtk::Button host_button_, cancel_button_;
	Gtk::Entry port_entry_, player_name_entry_;
	Gtk::Label port_label_, player_name_label_;
	void Host();
	void Cancel();
public:
	HostGameWindow(Glib::RefPtr<Gtk::Application> &app);
	~HostGameWindow() override;
};

#endif
