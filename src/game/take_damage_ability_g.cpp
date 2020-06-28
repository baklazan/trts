#include <take_damage_ability_g.h>
#include <full_game_state.h>

TakeDamageAbilityGame::TakeDamageAbilityGame(AbilityIDType id, EntityIDType entity_id) : VulnerAbility(id, entity_id),
                                                                      Searchable<TakeDamageAbilityGame>(entity_id) {
}

void TakeDamageAbilityGame::ReceiveDamage(int damage) {
    health_ = std::max(0, health_ - damage);
    if (health_ == 0) {
        FullGameState::GetInstance()->DestroyEntity(entity_id_);
    }
}
