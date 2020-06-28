#include <attack_task.h>
#include <attack_ability_u.h>
#include <take_damage_ability.h>
#include <occupy_space_ability.h>
#include <distance.h>
#include <move_task.h>

AttackTask::AttackTask(EntityIDType entity_id, EntityIDType target_entity_id) : Task(entity_id), target_entity_id_(target_entity_id) {
}

bool AttackTask::IsFinished() {
    AttackAbilityUI *my_attack_ability = Searchable<AttackAbilityUI>::Search(entity_id_);
    if (my_attack_ability == nullptr) {
        std::cerr << "I don't have an attack ability :(" << std::endl;
        return true;
    }
    OccupySpaceAbility *his_occupy_ability = Searchable<OccupySpaceAbility>::Search(target_entity_id_);
    if (his_occupy_ability == nullptr) {
        std::cerr << "He doesn't have an occupy ability :(" << std::endl;
        return true;
    }
    VulnerAbility *his_take_dmg_ability = Searchable<VulnerAbility>::Search(target_entity_id_);
    if (his_take_dmg_ability == nullptr) {
        std::cerr << "he cannot take damage :(" << std::endl;
        return true;
    }
    return false;
}

std::shared_ptr<Command> AttackTask::NextCommand() {
    AttackAbilityUI *my_attack_ability = Searchable<AttackAbilityUI>::Search(entity_id_);
    OccupySpaceAbility *his_occupy_ability = Searchable<OccupySpaceAbility>::Search(target_entity_id_);
    OccupySpaceAbility *my_occupy_ability = Searchable<OccupySpaceAbility>::Search(entity_id_);
    VulnerAbility *his_take_dmg_ability = Searchable<VulnerAbility>::Search(target_entity_id_);

    double my_x = my_occupy_ability->GetX(), my_y = my_occupy_ability->GetY();
    double his_x = his_occupy_ability->GetX(), his_y = his_occupy_ability->GetY();
    double his_r = his_occupy_ability->GetRadius();
    double my_range = my_attack_ability->GetRange() * 0.999;
    double distance = Distance(my_x, my_y, his_x, his_y);
    if (distance < my_range + his_r) {
        double target_x = my_x, target_y = my_y;
        double coef = std::min(my_range / distance, 1.0);
        target_x += coef * (his_x - my_x);
        target_y += coef * (his_y - my_y);
        return my_attack_ability->MakeCommand(target_x, target_y);
    }
    else {
        MoveTask move_task(entity_id_, his_x, his_y, his_r + my_range);
        return move_task.NextCommand();
    }
}
