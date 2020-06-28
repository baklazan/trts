#include <move_ability.h>

std::string MoveAbility::type_ = "move";

MoveAbility::MoveCommand::MoveCommand(AbilityIDType ability_id, double target_x, double target_y) : Command(ability_id),
                                                                                          target_x_(target_x),
                                                                                          target_y_(target_y) {

}

void MoveAbility::MoveCommand::ReadInternals(std::shared_ptr<FormattedReader> reader) {
    reader->Comment("target_x=");
    target_x_ = reader->Double();
    reader->MinorSeparator();

    reader->Comment("target_y=");
    target_y_ = reader->Double();
}

void MoveAbility::MoveCommand::WriteInternals(std::shared_ptr<FormattedWriter> writer) const {
    writer->Comment("target_x=");
    writer->Double(target_x_);
    writer->MinorSeparator();

    writer->Comment("target_y=");
    writer->Double(target_y_);
}

MoveAbility::MoveCommand::MoveCommand(AbilityIDType ability_id) : Command(ability_id) {
}

MoveAbility::MoveAbility(AbilityIDType id, EntityIDType entity_id) : Ability(id, entity_id) {
}

std::shared_ptr<MoveAbility::MoveCommand> MoveAbility::MakeCommand(double target_x, double target_y) {
    return std::make_shared<MoveAbility::MoveCommand>(id_, target_x, target_y);
}

void MoveAbility::ReadInternals(std::shared_ptr<FormattedReader> reader) {
    reader->Comment("speed=");
    speed_ = reader->Double();
}

void MoveAbility::WriteInternals(std::shared_ptr<FormattedWriter> writer) const {
    writer->Comment("speed=");
    writer->Double(speed_);
}

std::string MoveAbility::TypeString() const {
    return type_;
}

double MoveAbility::GetSpeed() const {
    return speed_;
}
