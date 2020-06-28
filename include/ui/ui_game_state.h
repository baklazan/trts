#ifndef TRTS_UI_GAME_STATE_H
#define TRTS_UI_GAME_STATE_H

#include <game_state.h>
#include <targetable_ability.h>

class UIGameState : public GameState {
    static UIGameState *instance_;
    UIGameState();
public:
    ~UIGameState();
    static std::shared_ptr<UIGameState> MakeInstance();
    static UIGameState* GetInstance();
};

#endif
