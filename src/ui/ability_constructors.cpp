#include <ability_reader.h>
#include <occupy_space_ability.h>
#include <move_ability_u.h>
#include <take_damage_ability.h>
#include <attack_ability_u.h>
#include <be_owned_ability.h>

void AbilityReader::LoadConstructors() {
    constructors_[OccupySpaceAbility::type_] = [](AbilityIDType id, EntityIDType entity_id){
        return std::shared_ptr<Ability>(new OccupySpaceAbility(id, entity_id));
    };
    constructors_[MoveAbility::type_] = [](AbilityIDType id, EntityIDType entity_id) {
        return std::shared_ptr<Ability>(new MoveAbilityUI(id, entity_id));
    };
    constructors_[VulnerAbility::type_] = [](AbilityIDType id, EntityIDType entity_id) {
        return std::shared_ptr<Ability>(new VulnerAbility(id, entity_id));
    };
    constructors_[AttackAbility::type_] = [](AbilityIDType id, EntityIDType entity_id) {
        return std::shared_ptr<Ability>(new AttackAbilityUI(id, entity_id));
    };
    constructors_[BeOwnedAbility::type_] = [](AbilityIDType id, EntityIDType entity_id) {
        return std::shared_ptr<Ability>(new BeOwnedAbility(id, entity_id));
    };
    initialized_ = true;
}
