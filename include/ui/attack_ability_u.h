#ifndef TRTS_ATTACK_ABILITY_U_H
#define TRTS_ATTACK_ABILITY_U_H

#include <attack_ability.h>
#include <targetable_ability.h>
#include <searchable.h>

class AttackAbilityUI : public AttackAbility, public TargetableAbility, public Searchable<AttackAbilityUI> {
public:
    AttackAbilityUI(AbilityIDType id, EntityIDType entity_id);
    bool WantsGroundTarget(const GroundTarget *target) override;
    bool WantsEntityTarget(const EntityTarget *target) override;
    std::shared_ptr<Task> ConsumeGroundTarget(const GroundTarget *target) override;
    std::shared_ptr<Task> ConsumeEntityTarget(const EntityTarget *target) override;
};

#endif
