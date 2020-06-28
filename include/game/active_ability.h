#ifndef TRTS_ACTIVE_ABILITY_H
#define TRTS_ACTIVE_ABILITY_H

#include <event.h>
#include <searchable.h>
#include <memory>
#include <formatted_reader.h>
#include <ability.h>

class ActiveAbility : public Searchable<ActiveAbility> {
private:
    EntityIDType owner_entity_id_;
public:
    ActiveAbility(AbilityIDType id, EntityIDType entity_id);
    virtual Event ParseCommand(std::shared_ptr<FormattedReader> reader) = 0;
    virtual bool AcceptsCommandsFrom(PlayerIDType player_id);
};


#endif

