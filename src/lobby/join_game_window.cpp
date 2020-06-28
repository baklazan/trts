#include <join_game_window.h>
#include <main_menu_window.h>
#include <join_lobby_window.h>

JoinGameWindow::JoinGameWindow(Glib::RefPtr<Gtk::Application> &app) : StateWindow(app) {
	set_title("Trts: join a game");
	
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
	
	host_ip_label_.set_text("Host IP address");
	layout_grid_.attach(host_ip_label_, 0, 1, 1, 1);
	layout_grid_.attach(host_ip_entry_, 1, 1, 1, 1);
	
	host_port_label_.set_text("Host port");
	layout_grid_.attach(host_port_label_, 0, 2, 1, 1);
	host_port_entry_.set_text("4247");
	layout_grid_.attach(host_port_entry_, 1, 2, 1, 1);
	
	join_button_.add_label("Join");
	join_button_.signal_clicked().connect(sigc::mem_fun(*this, &JoinGameWindow::Join));
	join_button_.set_hexpand(true);
	join_button_.set_vexpand(true);
	layout_grid_.attach(join_button_, 0, 3, 2, 1);
	
	cancel_button_.add_label("Cancel");
	cancel_button_.signal_clicked().connect(sigc::mem_fun(*this, &JoinGameWindow::Cancel));
	cancel_button_.set_hexpand(true);
	cancel_button_.set_vexpand(true);
	layout_grid_.attach(cancel_button_, 0, 4, 2, 1);
	
	show_all();
}

void JoinGameWindow::Join() {
	JoinLobbyWindow *join_lobby_window = new JoinLobbyWindow(app_, host_port_entry_.get_text() ,host_ip_entry_.get_text(), player_name_entry_.get_text());
	if (join_lobby_window->CreatedSuccessfully()) {
		Transition(join_lobby_window);
	}
	else {
		delete join_lobby_window;
	}
}

void JoinGameWindow::Cancel() {
	MainMenuWindow *main_menu_window = new MainMenuWindow(app_);
	Transition(main_menu_window);
}

JoinGameWindow::~JoinGameWindow() {
}
