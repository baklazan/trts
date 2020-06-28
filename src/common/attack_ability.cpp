#include <attack_ability.h>

std::string AttackAbility::type_ = "attack";

AttackAbility::AttackAbility(AbilityIDType id, EntityIDType entity_id) : Ability(id, entity_id) {
}

void AttackAbility::ReadInternals(std::shared_ptr<FormattedReader> reader) {
    reader->Comment("range=");
    range_ = reader->Double();
    reader->MinorSeparator();

    reader->Comment("damage=");
    damage_ = reader->Int();
}

void AttackAbility::WriteInternals(std::shared_ptr<FormattedWriter> writer) const {
    writer->Comment("range=");
    writer->Double(range_);
    writer->MinorSeparator();

    writer->Comment("damage=");
    writer->Int(damage_);
}

std::string AttackAbility::TypeString() const {
    return type_;
}

std::shared_ptr<AttackAbility::AttackCommand> AttackAbility::MakeCommand(double target_x, double target_y) {
    return std::make_shared<AttackAbility::AttackCommand>(id_, target_x, target_y);
}

int AttackAbility::GetDamage() const {
    return damage_;
}

double AttackAbility::GetRange() const {
    return range_;
}

AttackAbility::AttackCommand::AttackCommand(AbilityIDType ability_id) : Command(ability_id) {
}

AttackAbility::AttackCommand::AttackCommand(AbilityIDType ability_id, double target_x, double target_y) : Command(ability_id),
                                                                                                target_x_(target_x),
                                                                                                target_y_(target_y) {
}

void AttackAbility::AttackCommand::ReadInternals(std::shared_ptr<FormattedReader> reader) {
    reader->Comment("target_x=");
    target_x_ = reader->Double();
    reader->MinorSeparator();

    reader->Comment("target_y=");
    target_y_ = reader->Double();
}

void AttackAbility::AttackCommand::WriteInternals(std::shared_ptr<FormattedWriter> writer) const {
    writer->Comment("target_x=");
    writer->Double(target_x_);
    writer->MinorSeparator();

    writer->Comment("target_y=");
    writer->Double(target_y_);
}

