#include <entity.h>
#include <ability_reader.h>
#include <cmath>
#include <iostream>

Entity::Entity() = default;

void Entity::Read(std::shared_ptr<FormattedReader> reader) {
    reader->Comment("id=");
    id_ = reader->Int();
    reader->MinorSeparator();

    reader->Comment("n_abilities=");
    int n_abilities = reader->Int();
    reader->MajorSeparator();
    reader->EnterBlock();
    abilities_.clear();
    for (int i=0; i<n_abilities; i++) {
        abilities_.push_back(AbilityReader::Read(id_, reader));
        reader->MajorSeparator();
    }
    reader->EscapeBlock();
}

void Entity::Write(std::shared_ptr<FormattedWriter> writer) const {
    writer->Comment("id=");
    writer->Int(id_);
    writer->MinorSeparator();

    writer->Comment("n_abilities=");
    writer->Int(abilities_.size());
    writer->MajorSeparator();
    writer->EnterBlock();
    for (const auto &ability : abilities_) {
        ability->Write(writer);
        writer->MajorSeparator();
    }
    writer->EscapeBlock();
}

