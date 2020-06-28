#ifndef TRTS_OBSERVING_WIDGET_H
#define TRTS_OBSERVING_WIDGET_H
#include <istream>

class ObservingWidget {
public:
	virtual void UpdateState(std::istream &in) = 0;
};

#endif
