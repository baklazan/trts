#ifndef TRTS_GAME_STATE_H
#define TRTS_GAME_STATE_H

#include <string>
#include <vector>
#include <memory>
#include <terrain.h>
#include <entity.h>
#include <player.h>
#include <formatted_writer.h>
#include <formatted_reader.h>
#include <map>

class GameState {
protected:
    std::shared_ptr<Terrain> terrain_;
    std::map<EntityIDType, std::shared_ptr<Entity>> entities_;
    std::vector<std::shared_ptr<Player>> players_;
    int player_count_;
    GameState();

public:

    const std::shared_ptr<Terrain> GetTerrain() const;
    const std::map<EntityIDType, std::shared_ptr<Entity>> GetEntities() const;
    const std::vector<std::shared_ptr<Player>> GetPlayers() const;
    int GetPlayerCount() const;

    void Read(std::shared_ptr<FormattedReader> reader);
    void Write(std::shared_ptr<FormattedWriter> writer) const;
};


#endif
