#ifndef TRTS_PLAYER_SLOT_H
#define TRTS_PLAYER_SLOT_H
#include <string>
#include <gtkmm/label.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/grid.h>
#include <network_check_button.h>
#include <network_label.h>

class PlayerSlot {
private:
	NetworkLabel *name_label_;
	NetworkCheckButton *ready_button_;
	
public:
	bool used_;
	std::map<std::string, ObservingWidget*> observing_widgets_;
	std::map<std::string, ObservedWidget*> observed_widgets_;
	PlayerSlot(Gtk::Grid &grid, int row);
	PlayerSlot();
	~PlayerSlot();
	
	void SetDefaults();
	void RegisterObserver(MessageWriter *observer);
	void RemoveObserver(MessageWriter *observer);
	void SetSensitive(bool sensitive);
	void SetName(std::string name);
	Gtk::CheckButton *GetReadyButton();
};

#endif
