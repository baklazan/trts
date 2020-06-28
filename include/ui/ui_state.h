#ifndef TRTS_UI_STATE_H
#define TRTS_UI_STATE_H

#include <id_types.h>

constexpr EntityIDType kNoEntityId = -1;

class UIState {
public:
    EntityIDType selected_entity_id_;
    UIState();
};

#endif
