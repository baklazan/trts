#ifndef TRTS_FULL_GAME_STATE_H
#define TRTS_FULL_GAME_STATE_H

#include <game_state.h>
#include <queue>
#include <functional>
#include <active_ability.h>
#include <event.h>

class FullGameState : public GameState {
private:
    static FullGameState* instance_;
    FullGameState();

    int current_tick_;
    std::map<int, int> ability_owners_;

    std::priority_queue<Event> event_queue_;
    std::vector<EntityIDType> entities_to_destroy_;

public:
    static std::shared_ptr<FullGameState> MakeInstance();
    static FullGameState* GetInstance();
    ~FullGameState();

    void DestroyEntity(EntityIDType entity_id);

    void UpdatePlayer(PlayerIDType player_id, std::shared_ptr<FormattedWriter> &writer) const;
    void ReadCommands(PlayerIDType player_id, std::shared_ptr<FormattedReader> &reader);
    void SimulateTick();

    bool GameEnded();
    std::vector<bool> WhoWon();
};

#endif
