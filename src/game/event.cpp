#include <event.h>

void Event::operator()() {
    call_();
}

bool Event::operator<(const Event &e2) const {
    return priority_ < e2.priority_;
}

Event::Event(int priority, std::function<void()> call) : priority_(priority), call_(call) {}

