#include <message_writer.h>
#include <full_game_state.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

int main() {
    MessageWriter out(STDOUT_FILENO);

    PlayerIDType player_count;
    std::string map_filename, formatting_str;
    std::cin >> player_count >> map_filename >> formatting_str;
    std::string trash;
    getline(std::cin, trash);

    std::shared_ptr<FormattedReader> reader;
    std::shared_ptr<FormattedWriter> writer;

    if (formatting_str == "debug") {
        reader.reset(new DebugReader);
        writer.reset(new DebugWriter);
    }
    /*else if (formatting_str == "binary") {
        reader.reset(new BinaryReader);
        writer.reset(new BinaryWriter);
    }*/
    else std::cerr << "unknown format: " << formatting_str << std::endl;

    std::ifstream map_in(map_filename);
    reader->Reset(&map_in);
    std::shared_ptr<FullGameState> game_state = FullGameState::MakeInstance();
    std::cerr << "start reading" << std::endl;
    game_state->Read(reader);
    std::cerr << "finish reading" << std::endl;

    if (player_count != game_state->GetPlayerCount()) {
        std::cerr << "wrong number of players" << std::endl;
    }

    writer->Reset(&out);
    reader->Reset(&std::cin);

    for (int tick_counter = 0; ; tick_counter++) {
        if (game_state->GameEnded()) {
            out << "end";
            std::vector<bool> is_winner = game_state->WhoWon();
            for (PlayerIDType player_id = 0; player_id < player_count; player_id++) {
                out << " " << (is_winner[player_id] ? 1 : 0);
            }
            out << "\n";
            out.Flush();
            break;
        }
        out << "tick " << tick_counter << "\n";
        out.Flush();
        for (PlayerIDType player_id = 0; player_id < player_count; player_id++) {
            game_state->UpdatePlayer(player_id, writer);
            out.Flush();
        }
        for (PlayerIDType player_id = 0; player_id < player_count; player_id++) {
            game_state->ReadCommands(player_id, reader);
        }
        game_state->SimulateTick();
    }
    
    std::cerr << "game over" << std::endl;
    return 0;
}

