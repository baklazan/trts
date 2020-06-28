#include <active_ability.h>
#include <be_owned_ability.h>

ActiveAbility::ActiveAbility(AbilityIDType id, EntityIDType entity_id) : Searchable<ActiveAbility>(id), owner_entity_id_(entity_id) {
}

bool ActiveAbility::AcceptsCommandsFrom(PlayerIDType player_id) {
    BeOwnedAbility *owned_ability = Searchable<BeOwnedAbility>::Search(owner_entity_id_);
    if (owned_ability == nullptr) return false;
    return owned_ability->GetOwnerId() == player_id;
}

