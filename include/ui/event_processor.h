#ifndef TRTS_EVENT_PROCESSOR_H
#define TRTS_EVENT_PROCESSOR_H

#include <ui_game_state.h>
#include <task.h>
#include <target.h>
#include <ui_state.h>

class EventProcessor {
    int mouse_x_, mouse_y_;
public:
    EventProcessor();

    std::vector<std::shared_ptr<Task>>
    ProcessEvents(std::shared_ptr<UIGameState> game_state, std::shared_ptr<TargetPicker> target_picker,
                  std::shared_ptr<UIState> ui_state);
};

#endif
