#include <network_check_button.h>

NetworkCheckButton::NetworkCheckButton(std::string id) : ObservedWidget(id) {
	signal_toggled().connect(sigc::mem_fun(*this, &NetworkCheckButton::NotifyAll));
}

void NetworkCheckButton::PrintValue(std::ostream &out) {
	out << (get_active() ? "1" : "0");
}

void NetworkCheckButton::UpdateState(std::istream &in) {
	int new_state;
	in >> new_state;
	set_active(new_state);
}
