#ifndef TRTS_MOVE_ABILITY_U_H
#define TRTS_MOVE_ABILITY_U_H

#include <move_ability.h>
#include <targetable_ability.h>
#include <searchable.h>

class MoveAbilityUI : public MoveAbility, TargetableAbility, public Searchable<MoveAbilityUI> {
public:
    MoveAbilityUI(AbilityIDType id, EntityIDType entity_id);
    bool WantsGroundTarget(const GroundTarget *target) override;
    bool WantsEntityTarget(const EntityTarget *target) override;
    std::shared_ptr<Task> ConsumeGroundTarget(const GroundTarget *target) override;
    std::shared_ptr<Task> ConsumeEntityTarget(const EntityTarget *target) override;
};

#endif
