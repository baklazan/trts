#include <host_game_window.h>
#include <main_menu_window.h>
#include <host_lobby_window.h>

HostGameWindow::HostGameWindow(Glib::RefPtr<Gtk::Application> &app) : StateWindow(app) {
	set_title("Trts: host a game");
	
	set_default_size(300, 400);
	set_position(Gtk::WIN_POS_CENTER);
	
	add(layout_grid_);
	
	char name_buffer[128];
	int err = getlogin_r(name_buffer, 128);
	if (err < 0) {
		strcpy(name_buffer, "Player");
	}
	player_name_label_.set_text("Name");
	layout_grid_.attach(player_name_label_, 0, 0, 1, 1);
	player_name_entry_.set_text(name_buffer);
	layout_grid_.attach(player_name_entry_, 1, 0, 1, 1);
	
	port_label_.set_text("Port");
	layout_grid_.attach(port_label_, 0, 1, 1, 1);
	port_entry_.set_text("4247");
	layout_grid_.attach(port_entry_, 1, 1, 1, 1);
	
	host_button_.add_label("Host");
	host_button_.signal_clicked().connect(sigc::mem_fun(*this, &HostGameWindow::Host));
	host_button_.set_hexpand(true);
	host_button_.set_vexpand(true);
	layout_grid_.attach(host_button_, 0, 2, 2, 1);
	
	cancel_button_.add_label("Cancel");
	cancel_button_.signal_clicked().connect(sigc::mem_fun(*this, &HostGameWindow::Cancel));
	cancel_button_.set_hexpand(true);
	cancel_button_.set_vexpand(true);
	layout_grid_.attach(cancel_button_, 0, 3, 2, 1);
	
	show_all();
}

void HostGameWindow::Host() {
	HostLobbyWindow *host_lobby_window = new HostLobbyWindow(app_, port_entry_.get_text(), player_name_entry_.get_text());
	if (host_lobby_window->CreatedSuccessfully()) {
		Transition(host_lobby_window);
	}
	else {
		delete host_lobby_window;
	}
}

void HostGameWindow::Cancel() {
	MainMenuWindow *main_menu_window = new MainMenuWindow(app_);
	Transition(main_menu_window);
}

HostGameWindow::~HostGameWindow() {
	
}
