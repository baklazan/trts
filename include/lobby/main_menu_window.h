#ifndef TRTS_MAIN_MENU_WINDOW_H
#define TRTS_MAIN_MENU_WINDOW_H
#include <state_window.h>

class MainMenuWindow : public StateWindow {
private:
	Gtk::Grid layout_grid_;
	Gtk::Button join_game_button_, host_game_button_, quit_button_;
	void JoinGame();
	void HostGame();
	void Quit();
public:
	MainMenuWindow(Glib::RefPtr<Gtk::Application> &app);
	~MainMenuWindow() override;
};

#endif
