#include <player_slot.h>

PlayerSlot::PlayerSlot() = default;

PlayerSlot::PlayerSlot(Gtk::Grid &grid, int row) {
	std::ostringstream out;
	out << "player_" << row-1 << "_";
	std::string id_prefix = out.str();
	
	std::string ready_button_id = id_prefix + "ready";
	ready_button_ = new NetworkCheckButton(ready_button_id);
	observed_widgets_[ready_button_id] = ready_button_;
	observing_widgets_[ready_button_id] = ready_button_;
	grid.attach(*ready_button_, 1, row, 1, 1);
	
	std::string name_id = id_prefix + "name";
	name_label_ = new NetworkLabel(name_id);
	observed_widgets_[name_id] = name_label_;
	observing_widgets_[name_id] = name_label_;
	grid.attach(*name_label_, 0, row, 1, 1);
	
	SetDefaults();
}

void PlayerSlot::SetSensitive(bool sensitive) {
	ready_button_->set_sensitive(sensitive);
}

void PlayerSlot::SetDefaults() {
	used_ = false;
	ready_button_->set_active(false);
	name_label_->set_text("[empty slot]");
	SetSensitive(false);
}

void PlayerSlot::RegisterObserver(MessageWriter *observer) {
	for (auto widget : observed_widgets_) {
		widget.second->RegisterObserver(observer);
	}
}

void PlayerSlot::RemoveObserver(MessageWriter *observer) {
	for (auto widget : observed_widgets_) {
		widget.second->RemoveObserver(observer);
	}
}

void PlayerSlot::SetName(std::string name) {
	name_label_->set_text(name);
}

Gtk::CheckButton *PlayerSlot::GetReadyButton() {
	return ready_button_;
}


PlayerSlot::~PlayerSlot() {
	delete name_label_;
	delete ready_button_;
}
