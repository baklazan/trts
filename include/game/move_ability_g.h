#ifndef TRTS_MOVE_ABILITY_G_H
#define TRTS_MOVE_ABILITY_G_H

#include <move_ability.h>
#include <active_ability.h>

class MoveAbilityGame : public MoveAbility, ActiveAbility, public Searchable<MoveAbilityGame> {
    void MoveTo(double target_x, double target_y);
public:
    MoveAbilityGame(AbilityIDType id, EntityIDType entity_id);
    Event ParseCommand(std::shared_ptr<FormattedReader> reader) override;
};

#endif
