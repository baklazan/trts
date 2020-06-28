#ifndef TRTS_OBSERVED_WIDGET_H
#define TRTS_OBSERVED_WIDGET_H
#include <message_writer.h>
#include <set>

class ObservedWidget {
private:
	std::set<MessageWriter*> observers_;
	std::string id_;
public:
	
	ObservedWidget(std::string id = "");
	
	virtual void PrintValue(std::ostream &out) = 0;
	
	void Notify(MessageWriter *observer);
	void NotifyAll();
	void RegisterObserver(MessageWriter *observer);
	void RemoveObserver(MessageWriter *observer);
};

#endif
