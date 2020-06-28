#include <move_ability_g.h>
#include <occupy_space_ability.h>
#include <full_game_state.h>
#include <distance.h>

MoveAbilityGame::MoveAbilityGame(AbilityIDType id, EntityIDType entity_id) : MoveAbility(id, entity_id), ActiveAbility(id, entity_id),
                                                          Searchable<MoveAbilityGame>(entity_id) {
}

void MoveAbilityGame::MoveTo(double target_x, double target_y) {
    OccupySpaceAbility *occupy_ability = Searchable<OccupySpaceAbility>::Search(entity_id_);
    if (occupy_ability != nullptr) {
        double x = occupy_ability->GetX();
        double y = occupy_ability->GetY();
        if (Distance(x, y, target_x, target_y) <= speed_) {
            occupy_ability->ChangePosition(target_x, target_y);
        }
    }
}

Event MoveAbilityGame::ParseCommand(std::shared_ptr<FormattedReader> reader) {
    std::shared_ptr<MoveAbility::MoveCommand> command(new MoveAbility::MoveCommand(id_));
    command->ReadInternals(reader);
    EntityIDType my_entity_id = entity_id_;
    std::function<void()> call = [my_entity_id, command]() {
        MoveAbilityGame *this_ability = Searchable<MoveAbilityGame>::Search(my_entity_id);
        if (this_ability != nullptr) {
            this_ability->MoveTo(command->target_x_, command->target_y_);
        }
    };
    return Event(0, call);
}
