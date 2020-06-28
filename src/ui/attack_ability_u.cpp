#include <attack_ability_u.h>
#include <iostream>
#include <attack_task.h>
#include <be_owned_ability.h>

AttackAbilityUI::AttackAbilityUI(AbilityIDType id, EntityIDType entity_id) : AttackAbility(id, entity_id),
                                                          TargetableAbility(id, entity_id),
                                                          Searchable<AttackAbilityUI>(entity_id) {
}

bool AttackAbilityUI::WantsGroundTarget(const GroundTarget *target) {
    return false;
}

bool AttackAbilityUI::WantsEntityTarget(const EntityTarget *target) {
    BeOwnedAbility *his_owned_ability = Searchable<BeOwnedAbility>::Search(target->entity_id_);
    BeOwnedAbility *my_owned_ability = Searchable<BeOwnedAbility>::Search(entity_id_);
    if (his_owned_ability != nullptr && my_owned_ability != nullptr) {
        if (his_owned_ability->GetOwnerId() == my_owned_ability->GetOwnerId()) return false;
    }
    return true;
}

std::shared_ptr<Task> AttackAbilityUI::ConsumeGroundTarget(const GroundTarget *target) {
    std::cerr << "invalid target" << std::endl;
    return std::shared_ptr<Task>(nullptr);
}

std::shared_ptr<Task> AttackAbilityUI::ConsumeEntityTarget(const EntityTarget *target) {
    return std::shared_ptr<Task>(new AttackTask(entity_id_, target->entity_id_));
}
