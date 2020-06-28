#include <full_game_state.h>
#include <iostream>
#include <game_state.h>
#include <cmath>
#include <be_owned_ability.h>

FullGameState* FullGameState::instance_ = nullptr;

void FullGameState::UpdatePlayer(PlayerIDType player_id, std::shared_ptr<FormattedWriter> &writer) const {
    Write(writer);
}

void FullGameState::ReadCommands(PlayerIDType player_id, std::shared_ptr<FormattedReader> &reader) {
    reader->Comment("n_commands=");
    int n_commands = reader->Int();
    reader->MajorSeparator();
    reader->EnterBlock();
    for (int i=0; i<n_commands; i++) {
        reader->Comment("ability_id=");
        AbilityIDType ability_id = reader->Int();
        reader->MinorSeparator();
        ActiveAbility *ability = Searchable<ActiveAbility>::Search(ability_id);
        if (ability != nullptr) {
            Event event = ability->ParseCommand(reader);
            if (ability->AcceptsCommandsFrom(player_id)) {
                event_queue_.push(event);
            }
        }
        reader->MajorSeparator();
    }
    reader->EscapeBlock();
}

void FullGameState::SimulateTick() {
    while (! event_queue_.empty()) {
        Event event = event_queue_.top();
        event_queue_.pop();
        event();
    }
    for (EntityIDType entity_id : entities_to_destroy_) {
        entities_.erase(entity_id);
    }
    current_tick_ ++;
}

bool FullGameState::GameEnded() {
    return current_tick_ >= 300;
}

std::vector<bool> FullGameState::WhoWon() {
    return std::vector<bool>(player_count_, true);
}

FullGameState::FullGameState() : current_tick_(0) {
}

FullGameState* FullGameState::GetInstance() {
    return instance_;
}

FullGameState::~FullGameState() {
    instance_ = nullptr;
}

std::shared_ptr<FullGameState> FullGameState::MakeInstance() {
    if (instance_ != nullptr) {
        return nullptr;
    }
    instance_ = new FullGameState;
    return std::shared_ptr<FullGameState>(instance_);
}

void FullGameState::DestroyEntity(EntityIDType entity_id) {
    entities_to_destroy_.push_back(entity_id);
}


