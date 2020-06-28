#ifndef TRTS_TAKE_DAMAGE_ABILITY_G_H
#define TRTS_TAKE_DAMAGE_ABILITY_G_H

#include <take_damage_ability.h>

class TakeDamageAbilityGame : public VulnerAbility, public Searchable<TakeDamageAbilityGame> {
public:
    TakeDamageAbilityGame(AbilityIDType id, EntityIDType entity_id);
    void ReceiveDamage(int damage);
};

#endif
