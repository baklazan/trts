#ifndef TRTS_NETWORK_LABEL_H
#define TRTS_NETWORK_LABEL_H
#include <gtkmm/label.h>
#include <observed_widget.h>
#include <observing_widget.h>

class NetworkLabel : public Gtk::Label, public ObservedWidget, public ObservingWidget {
public:
	NetworkLabel(std::string id="");
	void PrintValue(std::ostream &out) override;
	void UpdateState(std::istream &in) override;
	void set_text(const Glib::ustring &str);
};

#endif
