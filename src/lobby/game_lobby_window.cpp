#include <game_lobby_window.h>
#include <main_menu_window.h>

constexpr unsigned kMaxNumberOfPlayers = 6;

GameLobbyWindow::GameLobbyWindow(Glib::RefPtr<Gtk::Application> &app) : StateWindow(app) {
	set_title("Trts: Game lobby");
	set_default_size(960, 600);
	set_position(Gtk::WIN_POS_CENTER);
	
	add(layout_grid_);
	
	layout_grid_.attach(players_grid_, 0, 0, 2, 1);
	player_name_label_.set_text("Name");
	players_grid_.attach(player_name_label_, 0, 0, 1, 1);
	ready_label_.set_text("Ready");
	players_grid_.attach(ready_label_, 1, 0, 1, 1);
	for (unsigned i=0; i < kMaxNumberOfPlayers; i++) {
		PlayerSlot *slot = new PlayerSlot(players_grid_, i+1);
		player_slots_.push_back(slot);
		for (auto it : slot->observing_widgets_) {
			observing_widgets_[it.first] = it.second;
		}
		for (auto it : slot->observed_widgets_) {
			observed_widgets_[it.first] = it.second;
		}
	}
	
	layout_grid_.attach(chat_grid_, 0, 1, 2, 1);
	layout_grid_.attach(settings_grid_, 2, 0, 1, 3);
	
	cancel_button_.signal_clicked().connect(sigc::mem_fun(*this, &GameLobbyWindow::Cancel));
	cancel_button_.add_label("Cancel");
	layout_grid_.attach(cancel_button_, 0, 2, 1, 1);
	
	start_button_.add_label("Start");
	layout_grid_.attach(start_button_, 1, 2, 1, 1);
	
	show_all();
}

void GameLobbyWindow::ParseCommand(std::string command) {
	std::istringstream in(command);
	std::string id;
	in >> id;
	if (observing_widgets_.count(id) == 0) {
		fprintf(stderr,"Warning: Unknown command: %s\n", id.c_str());
		return;
	}
	observing_widgets_[id]->UpdateState(in);
}

void GameLobbyWindow::Cancel() {
	MainMenuWindow *main_menu_window = new MainMenuWindow(app_);
	Transition(main_menu_window);
}

GameLobbyWindow::~GameLobbyWindow() {
	for (auto player_slot : player_slots_) {
		delete player_slot;
	}
}
