#include <attack_ability_g.h>
#include <occupy_space_ability.h>
#include <take_damage_ability_g.h>
#include <vector>
#include <distance.h>
#include <be_owned_ability.h>

AttackAbilityGame::AttackAbilityGame(AbilityIDType id, EntityIDType entity_id) : AttackAbility(id, entity_id), ActiveAbility(id, entity_id),
                                                              Searchable<AttackAbilityGame>(entity_id) {
}

Event AttackAbilityGame::ParseCommand(std::shared_ptr<FormattedReader> reader) {
    std::shared_ptr<AttackCommand> command(new AttackCommand(id_));
    command->ReadInternals(reader);
    EntityIDType my_entity_id = entity_id_;
    std::function<void()> call = [my_entity_id, command]() {
        AttackAbilityGame *this_ability = Searchable<AttackAbilityGame>::Search(my_entity_id);
        if (this_ability != nullptr) {
            this_ability->Attack(command->target_x_, command->target_y_);
        }
    };
    return Event(10, call);
}

void AttackAbilityGame::Attack(double target_x, double target_y) {
    OccupySpaceAbility *occupy_ability = Searchable<OccupySpaceAbility>::Search(entity_id_);
    if (occupy_ability == nullptr) return;
    double my_x = occupy_ability->GetX(), my_y = occupy_ability->GetY();
    if (Distance(my_x, my_y, target_x, target_y) <= range_) {
        BeOwnedAbility *my_owned_ability = Searchable<BeOwnedAbility>::Search(entity_id_);

        std::vector<EntityIDType> damaged = OccupySpaceAbility::EntitiesAtPoint(target_x, target_y);
        for (EntityIDType target_entity_id : damaged) {
            if (target_entity_id == entity_id_) continue;

            BeOwnedAbility *his_owned_ability = Searchable<BeOwnedAbility>::Search(target_entity_id);
            if (his_owned_ability != nullptr && my_owned_ability != nullptr) {
                if (my_owned_ability->GetOwnerId() == his_owned_ability->GetOwnerId()) {
                    continue;
                }
            }


            TakeDamageAbilityGame *take_damage_ability = Searchable<TakeDamageAbilityGame>::Search(target_entity_id);
            if (take_damage_ability != nullptr) {
                take_damage_ability->ReceiveDamage(damage_);
            }
        }
    }
}
