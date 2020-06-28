#include <ability.h>
#include <iostream>

Ability::Ability(AbilityIDType id, EntityIDType entity_id) : id_(id), entity_id_(entity_id) {

}

void Ability::Write(std::shared_ptr<FormattedWriter> writer) const {
    writer->Token(TypeString());
    writer->MinorSeparator();

    writer->Comment("id=");
    writer->Int(id_);
    writer->MinorSeparator();

    WriteInternals(writer);
}
