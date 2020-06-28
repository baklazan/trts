#include <ability_reader.h>
#include <entity.h>

bool AbilityReader::initialized_ = false;
std::map<std::string, std::function<std::shared_ptr<Ability>(AbilityIDType, EntityIDType)>> AbilityReader::constructors_;

std::shared_ptr<Ability> AbilityReader::Construct(AbilityIDType id, EntityIDType entity_id, std::string type) {
    if (!initialized_) {
        LoadConstructors();
    }
    return constructors_[type](id, entity_id);
}

std::shared_ptr<Ability> AbilityReader::Read(EntityIDType entity_id, std::shared_ptr<FormattedReader> reader) {
    std::string type = reader->Token();
    reader->MinorSeparator();

    reader->Comment("id=");
    AbilityIDType id = reader->Int();
    reader->MinorSeparator();

    std::shared_ptr<Ability> ability = Construct(id, entity_id, type);
    ability->ReadInternals(reader);
    return ability;
}
