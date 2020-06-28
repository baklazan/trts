#include <move_ability_u.h>
#include <iostream>
#include <ui_game_state.h>
#include <move_task.h>

bool MoveAbilityUI::WantsGroundTarget(const GroundTarget *target) {
    return true;
}

bool MoveAbilityUI::WantsEntityTarget(const EntityTarget *target) {
    return false;
}

std::shared_ptr<Task> MoveAbilityUI::ConsumeGroundTarget(const GroundTarget *target) {
    return std::shared_ptr<Task>(new MoveTask(entity_id_, target->x_, target->y_, 0.001));
}

std::shared_ptr<Task> MoveAbilityUI::ConsumeEntityTarget(const EntityTarget *target) {
    std::cerr << "invalid target" << std::endl;
    return std::shared_ptr<Task>(nullptr);
}

MoveAbilityUI::MoveAbilityUI(AbilityIDType id, EntityIDType entity_id) : TargetableAbility(id, entity_id), MoveAbility(id, entity_id),
                                                      Searchable<MoveAbilityUI>(entity_id) {
}

