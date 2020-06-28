#ifndef TRTS_EVENT_H
#define TRTS_EVENT_H

#include <functional>

class Event {
    int priority_;
    std::function<void()> call_;
public:
    Event(int priority, std::function<void()> call);
    void operator() ();
    bool operator< (const Event &e2) const;
};


#endif //TRTS_EVENT_H
