#include <state_window.h>

StateWindow::StateWindow(Glib::RefPtr<Gtk::Application> &app) {
	app_ = app;
	signal_delete_event().connect(sigc::mem_fun(*this, &StateWindow::CloseHandler));
}

void StateWindow::Register() {
	set_application(app_);
	show();
}

void StateWindow::Transition(StateWindow *new_window) {
	if (new_window != nullptr) {
		new_window->Register();
	}
	delete this;
}

StateWindow::~StateWindow() {
	app_->remove_window(*this);
}

bool StateWindow::CloseHandler(GdkEventAny* any_event) {
	delete this;
	return true;
}
