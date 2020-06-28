#ifndef TRTS_GAME_LOBBY_WINDOW_H
#define TRTS_GAME_LOBBY_WINDOW_H
#include <state_window.h>
#include <player_slot.h>

class GameLobbyWindow : public StateWindow {
protected:
	Gtk::Grid layout_grid_, players_grid_, settings_grid_, chat_grid_;
	Gtk::Button start_button_, cancel_button_;
	Gtk::Label player_name_label_, ready_label_;
	std::vector<PlayerSlot*> player_slots_;
	std::map<std::string, ObservedWidget*> observed_widgets_;
	std::map<std::string, ObservingWidget*> observing_widgets_;
	void Cancel();
	virtual void ParseCommand(std::string command);
	
public:
	GameLobbyWindow(Glib::RefPtr<Gtk::Application> &app);
	
	virtual ~GameLobbyWindow() override;
};

#endif
