#include <network_label.h>

NetworkLabel::NetworkLabel(std::string id) : ObservedWidget(id) { }

void NetworkLabel::PrintValue(std::ostream &out) {
	out << get_text();
}

void NetworkLabel::set_text(const Glib::ustring &str) {
	Gtk::Label::set_text(str);
	NotifyAll();
}

void NetworkLabel::UpdateState(std::istream &in) {
	std::string text;
	getline(in, text);
	set_text(text);
}
