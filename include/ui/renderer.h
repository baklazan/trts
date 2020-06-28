#ifndef TRTS_RENDERER_H
#define TRTS_RENDERER_H

#include <memory>
#include <game_state.h>
#include <SDL/SDL.h>
#include <ui_state.h>
#include <target.h>

class Renderer {
    std::vector<SDL_Surface*> tile_imgs_;
public:
    Renderer();
    ~Renderer();
    std::shared_ptr<TargetPicker> Render(std::shared_ptr<GameState> game_state, std::shared_ptr<UIState> ui_state, SDL_Surface *screen);
};

#endif
