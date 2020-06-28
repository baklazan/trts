#include <move_task.h>
#include <occupy_space_ability.h>
#include <move_ability_u.h>
#include <distance.h>


bool MoveTask::IsFinished() {
    OccupySpaceAbility *occupy_ability = Searchable<OccupySpaceAbility>::Search(entity_id_);
    if (occupy_ability == nullptr) return true;
    double dx = occupy_ability->GetX() - target_x_, dy = occupy_ability->GetY() - target_y_;
    return dx * dx + dy * dy <= target_distance_ * target_distance_;
}

std::shared_ptr<Command> MoveTask::NextCommand() {
    OccupySpaceAbility *occupy_ability = Searchable<OccupySpaceAbility>::Search(entity_id_);
    MoveAbilityUI *move_ability = Searchable<MoveAbilityUI>::Search(entity_id_);
    double speed = move_ability->GetSpeed();
    double entity_x = occupy_ability->GetX(), entity_y = occupy_ability->GetY();
    double distance = Distance(entity_x, entity_y, target_x_, target_y_);

    double next_step_x = target_x_, next_step_y = target_y_;
    if (distance > speed) {
        double coef = 0.999 * speed / distance;
        next_step_x = (target_x_ - entity_x) * coef + entity_x;
        next_step_y = (target_y_ - entity_y) * coef + entity_y;
    }
    return move_ability->MakeCommand(next_step_x, next_step_y);
}

MoveTask::MoveTask(EntityIDType entity_id, double target_x, double target_y, double target_distance) : Task(entity_id),
                                                                                              target_x_(target_x),
                                                                                              target_y_(target_y),
                                                                                              target_distance_(
                                                                                                      target_distance) {

}
