#include <renderer.h>

#include <occupy_space_ability.h>
#include <take_damage_ability.h>

Renderer::Renderer() {
    tile_imgs_.push_back(SDL_LoadBMP("assets/flat3x3.bmp"));
    tile_imgs_.push_back(SDL_LoadBMP("assets/water.bmp"));
}

std::shared_ptr<TargetPicker>
Renderer::Render(std::shared_ptr<GameState> game_state, std::shared_ptr<UIState> ui_state, SDL_Surface *screen) {
    std::shared_ptr<Terrain> terrain = game_state->GetTerrain();
    for (int y=0; y<terrain->height_; y++) {
        for (int x = 0; x < terrain->width_; x++) {
            SDL_Rect rect;
            rect.x = x * 60;
            rect.y = y * 60;
            rect.w = 60;
            rect.h = 60;
            SDL_Rect from_rect;
            SDL_Surface *img = tile_imgs_[terrain->tiles_[y][x]];
            from_rect.w = 60;
            from_rect.h = 60;
            from_rect.x = 60 * (rand() % (img->w / 60));
            from_rect.y = 60 * (rand() % (img->h / 60));
            SDL_BlitSurface(img, &from_rect, screen, &rect);
        }
    }

    std::vector<std::vector<EntityIDType>> target_map(screen->h, std::vector<EntityIDType> (screen->w, kNoEntityId));
    std::map<EntityIDType, std::shared_ptr<Entity>> entities = game_state->GetEntities();

    uint8_t *pixels = reinterpret_cast<uint8_t*>(screen->pixels);
    int bpp = screen->format->BytesPerPixel;
    for (const auto &item : entities) {
        EntityIDType entity_id = item.first;
        OccupySpaceAbility *occupy_ability = Searchable<OccupySpaceAbility>::Search(entity_id);
        if (occupy_ability != nullptr) {
            int color[4] = {0, 0, 0, 0};
            if (entity_id == ui_state->selected_entity_id_) color[0] = 255;
            VulnerAbility *takedmg_ability = Searchable<VulnerAbility>::Search(entity_id);
            if (takedmg_ability != nullptr) {
                color[2] = 255 * takedmg_ability->GetHealth() / takedmg_ability->GetMaxHealth();
            }

            double mid_x = occupy_ability->GetX(), mid_y = occupy_ability->GetY(), radius = occupy_ability->GetRadius();
            int min_x = std::max(0, static_cast<int>((mid_x - radius) * 60 + 0.5));
            int max_x = std::min(screen->w-1, static_cast<int>((mid_x + radius) * 60 - 0.5));
            int min_y = std::max(0, static_cast<int>((mid_y - radius) * 60 + 0.5));
            int max_y = std::min(screen->h-1, static_cast<int>((mid_y + radius) * 60 - 0.5));
            for (int y=min_y; y <= max_y; y++) {
                for (int x=min_x; x <= max_x; x++) {
                    double real_x = (x+0.5) / 60.0, real_y = (y+0.5) / 60.0;
                    double dx = mid_x - real_x, dy = mid_y - real_y;
                    if (dx * dx + dy * dy <= radius * radius) {
                        target_map[y][x] = entity_id;
                        for (int i=0; i<bpp; i++) {
                            pixels[y * screen->pitch + x * bpp + i] = color[i];
                        }
                    }
                }
            }
        }
    }

    return std::make_shared<TargetPicker>(target_map, 0, 0, 60);
}

Renderer::~Renderer() {
    for (SDL_Surface *img : tile_imgs_) {
        SDL_FreeSurface(img);
    }
}
