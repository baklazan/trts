#include <ui_game_state.h>
#include <iostream>

UIGameState* UIGameState::instance_ = nullptr;

UIGameState::UIGameState() : GameState(){
}

UIGameState* UIGameState::GetInstance() {
    return instance_;

}

UIGameState::~UIGameState() {
    instance_ = nullptr;
}

std::shared_ptr<UIGameState> UIGameState::MakeInstance() {
    if (instance_ != nullptr) {
        return nullptr;
    }
    instance_ = new UIGameState;
    return std::shared_ptr<UIGameState>(instance_);
}


