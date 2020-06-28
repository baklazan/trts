#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>
#include <message_writer.h>
#include <unistd.h>
#include <ui_game_state.h>
#include <map>
#include <renderer.h>
#include <event_processor.h>

constexpr int kWidth = 900, kHeight = 600;

int main() {
    MessageWriter out(STDOUT_FILENO);
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface *screen;
    screen = SDL_SetVideoMode(kWidth, kHeight, 32, SDL_HWSURFACE);

    std::shared_ptr<UIGameState> game_state = UIGameState::MakeInstance();
    std::shared_ptr<FormattedWriter> writer(new DebugWriter);
    std::shared_ptr<FormattedReader> reader(new DebugReader);
    writer->Reset(&out);
    reader->Reset(&std::cin);

    std::shared_ptr<Renderer> renderer(new Renderer);
    std::shared_ptr<UIState> ui_state(new UIState);
    std::shared_ptr<EventProcessor> event_processor(new EventProcessor);
    std::shared_ptr<TargetPicker> target_picker(nullptr), next_target_picker;
    std::map<EntityIDType, std::shared_ptr<Task>> tasks_by_entity_id;


    while (true) {
        std::string ui_command;
        std::cin >> ui_command;
        if (ui_command == "tick") {
            std::string trash;
            getline(std::cin, trash);
            game_state->Read(reader);
            next_target_picker = renderer->Render(game_state, ui_state, screen);

            SDL_Flip(screen);

            if (target_picker != nullptr) {
                std::vector<std::shared_ptr<Task>> new_tasks = event_processor->ProcessEvents(game_state, target_picker,
                                                                                              ui_state);
                for (auto task : new_tasks) {
                    tasks_by_entity_id[task->entity_id_] = task;
                }
            }
            target_picker = next_target_picker;
            std::vector<std::shared_ptr<Command>> commands;

            for (const auto &item : tasks_by_entity_id) {
                EntityIDType entity_id = item.first;
                auto task = item.second;
                if (task->IsFinished()) {
                    tasks_by_entity_id.erase(entity_id);
                } else {
                    commands.push_back(task->NextCommand());
                }
            }

            writer->Comment("n_commands=");
            writer->Int(commands.size());
            writer->MajorSeparator();
            writer->EnterBlock();
            for (auto command : commands) {
                command->Write(writer);
                writer->MajorSeparator();
            }
            writer->EscapeBlock();
            out.Flush();

        } else if (ui_command == "end") {
            SDL_Rect rect;

            rect.x = 300;
            rect.y = 250;
            rect.w = 300;
            rect.h = 100;

            std::string result;
            std::cin >> result;
            std::string filename = "assets/";
            filename += result;
            filename += ".bmp";
            SDL_Surface *img = SDL_LoadBMP(filename.c_str());
            SDL_BlitSurface(img, nullptr, screen, &rect);
            SDL_FreeSurface(img);
            SDL_Flip(screen);
            break;
        } else {
            std::cerr << "unknown command: " << ui_command << std::endl;
            return 0;
        }
    }

    bool want_to_quit = false;
    while (!want_to_quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                want_to_quit = true;
                break;
            }
        }
    }
    
    renderer.reset();
    SDL_Quit();
    
    return 0;
}
