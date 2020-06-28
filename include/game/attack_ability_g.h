#ifndef TRTS_ATTACK_ABILITY_G_H
#define TRTS_ATTACK_ABILITY_G_H

#include <attack_ability.h>
#include <active_ability.h>

class AttackAbilityGame : public AttackAbility, ActiveAbility, public Searchable<AttackAbilityGame> {
    void Attack(double target_x, double target_y);
public:
    AttackAbilityGame(AbilityIDType id, EntityIDType entity_id);
    Event ParseCommand(std::shared_ptr<FormattedReader> reader) override;
};

#endif
