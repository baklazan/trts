#ifndef TRTS_NETWORK_CHECK_BUTTON_H
#define TRTS_NETWORK_CHECK_BUTTON_H
#include <gtkmm/checkbutton.h>
#include <observed_widget.h>
#include <observing_widget.h>

class NetworkCheckButton : public Gtk::CheckButton, public ObservingWidget, public ObservedWidget {
public:
	NetworkCheckButton(std::string id="");
	void PrintValue(std::ostream &out) override;
	void UpdateState(std::istream &in) override;
};

#endif
