#include <main_menu_window.h>
#include <gtkmm/application.h>

int main(int argc, char **argv) {
	auto app = Gtk::Application::create(argc, argv, "");
	
	MainMenuWindow *main_menu_window = new MainMenuWindow(app);
	app->run(*main_menu_window);
	return 0;
}
