#include <main_menu_window.h>
#include <join_game_window.h>
#include <host_game_window.h>

MainMenuWindow::MainMenuWindow(Glib::RefPtr<Gtk::Application> &app) : StateWindow(app) { 
	set_title("Trts: Real Time Strategy");
	
	set_default_size(300, 400);
	set_position(Gtk::WIN_POS_CENTER);
	
	add(layout_grid_);
	
	host_game_button_.add_label("Host game");
	host_game_button_.signal_clicked().connect(sigc::mem_fun(*this, &MainMenuWindow::HostGame));
	host_game_button_.set_hexpand(true);
	host_game_button_.set_vexpand(true);
	layout_grid_.attach(host_game_button_, 0, 1, 1, 1);
	
	join_game_button_.add_label("Join game");
	join_game_button_.signal_clicked().connect(sigc::mem_fun(*this, &MainMenuWindow::JoinGame));
	join_game_button_.set_hexpand(true);
	join_game_button_.set_vexpand(true);
	layout_grid_.attach(join_game_button_, 0, 2, 1, 1);
	
	quit_button_.add_label("Quit game");
	quit_button_.signal_clicked().connect(sigc::mem_fun(*this, &MainMenuWindow::Quit));
	quit_button_.set_hexpand(true);
	quit_button_.set_vexpand(true);
	layout_grid_.attach(quit_button_, 0, 3, 1, 1);
	
	show_all();
}

void MainMenuWindow::JoinGame() {
	JoinGameWindow *join_game_window = new JoinGameWindow(app_);
	Transition(join_game_window);
}

void MainMenuWindow::HostGame() {
	HostGameWindow *host_game_window = new HostGameWindow(app_);
	Transition(host_game_window);
}

void MainMenuWindow::Quit() {
	delete this;
}

MainMenuWindow::~MainMenuWindow() {
	
}
