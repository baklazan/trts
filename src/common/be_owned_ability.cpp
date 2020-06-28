#include <be_owned_ability.h>

std::string BeOwnedAbility::type_ = "be_owned";

BeOwnedAbility::BeOwnedAbility(AbilityIDType id, EntityIDType entity_id) : Ability(id, entity_id), Searchable<BeOwnedAbility>(entity_id) {
}

std::string BeOwnedAbility::TypeString() const {
    return type_;
}

void BeOwnedAbility::ReadInternals(std::shared_ptr<FormattedReader> reader) {
    reader->Comment("owner_id=");
    owner_id_ = reader->Int();
}

void BeOwnedAbility::WriteInternals(std::shared_ptr<FormattedWriter> writer) const {
    writer->Comment("owner_id=");
    writer->Int(owner_id_);
}

PlayerIDType BeOwnedAbility::GetOwnerId() const {
    return owner_id_;
}
