#include <game_state.h>
#include <fstream>
#include <iostream>

GameState::GameState() {
    terrain_ = std::make_shared<Terrain>();
}

void GameState::Read(std::shared_ptr<FormattedReader> reader) {
    terrain_->Read(reader);
    reader->Comment("n_players=");
    player_count_ = reader->Int();
    reader->MajorSeparator();

    reader->EnterBlock();
    for (int player_id=0; player_id<player_count_; player_id++) {
        players_.emplace_back(new Player);
        players_.back()->Read(reader);
    }
    reader->EscapeBlock();

    reader->Comment("n_units=");
    int units_count = reader->Int();
    reader->MajorSeparator();
    reader->EnterBlock();
    entities_.clear();
    for (int j=0; j<units_count; j++) {
        std::shared_ptr<Entity> unit(new Entity);
        unit->Read(reader);
        entities_[unit->id_] = unit;
    }
    reader->EscapeBlock();
}

void GameState::Write(std::shared_ptr<FormattedWriter> writer) const {
    terrain_->Write(writer);
    writer->Comment("n_players=");
    writer->Int(player_count_);
    writer->MajorSeparator();

    writer->EnterBlock();
    for (const auto &player : players_) {
        player->Write(writer);
    }
    writer->EscapeBlock();

    writer->Comment("n_units=");
    writer->Int(entities_.size());
    writer->MajorSeparator();
    writer->EnterBlock();
    for (const auto &item : entities_) {
        item.second->Write(writer);
    }
    writer->EscapeBlock();
}


const std::map<EntityIDType, std::shared_ptr<Entity>> GameState::GetEntities() const {
    return entities_;
}

const std::vector<std::shared_ptr<Player>> GameState::GetPlayers() const {
    return players_;
}

int GameState::GetPlayerCount() const {
    return player_count_;
}


const std::shared_ptr<Terrain> GameState::GetTerrain() const {
    return terrain_;
}

