#ifndef TRTS_STATE_WINDOW_H
#define TRTS_STATE_WINDOW_H
#include <gtkmm.h>

class StateWindow : public Gtk::Window {
private:
	bool CloseHandler(GdkEventAny* any_event);
protected:
	Glib::RefPtr<Gtk::Application> app_;
	
	void Register();
	void Transition(StateWindow *new_window);
	virtual ~StateWindow();
public:
	StateWindow(Glib::RefPtr<Gtk::Application> &app);
};

#endif
