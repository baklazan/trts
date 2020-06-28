#include <take_damage_ability.h>

std::string VulnerAbility::type_ = "take_damage";

void VulnerAbility::ReadInternals(std::shared_ptr<FormattedReader> reader) {
    reader->Comment("max_health=");
    max_health_ = reader->Int();
    reader->MinorSeparator();

    reader->Comment("health=");
    health_ = reader->Int();
}

void VulnerAbility::WriteInternals(std::shared_ptr<FormattedWriter> writer) const {
    writer->Comment("max_health=");
    writer->Int(max_health_);
    writer->MinorSeparator();

    writer->Comment("health=");
    writer->Int(health_);
}

std::string VulnerAbility::TypeString() const {
    return type_;
}

VulnerAbility::VulnerAbility(AbilityIDType id, EntityIDType entity_id) : Ability(id, entity_id), Searchable<VulnerAbility>(entity_id) {
}

int VulnerAbility::GetHealth() const {
    return health_;
}

int VulnerAbility::GetMaxHealth() const {
    return max_health_;
}
