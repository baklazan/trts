#include <event_processor.h>
#include <SDL/SDL.h>

std::vector<std::shared_ptr<Task>>
EventProcessor::ProcessEvents(std::shared_ptr<UIGameState> game_state, std::shared_ptr<TargetPicker> target_picker,
                              std::shared_ptr<UIState> ui_state) {
    std::vector<std::shared_ptr<Task>> tasks;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_MOUSEMOTION: {
                mouse_x_ = event.motion.x;
                mouse_y_ = event.motion.y;
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                std::shared_ptr<Target> target = target_picker->PickTarget(mouse_x_, mouse_y_);
                if (event.button.button == SDL_BUTTON_LEFT) {
                    target->GetSelected(ui_state);
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    EntityIDType entity_id = ui_state->selected_entity_id_;
                    if (entity_id != kNoEntityId) {
                        std::map<AbilityIDType, TargetableAbility*> abilities = MultiSearchable<TargetableAbility>::Search(entity_id);
                        for (const auto &item : abilities) {
                            TargetableAbility *ability = item.second;
                            if (target->IsWanted(ability)) {
                                tasks.push_back(target->BeConsumed(ability));
                            }
                        }
                    }
                }
                break;
            }
        }
    }

    return tasks;
}

EventProcessor::EventProcessor() : mouse_x_(0), mouse_y_(0) {
}
