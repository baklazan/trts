#ifndef TRTS_ABILITY_READER_H
#define TRTS_ABILITY_READER_H

#include <ability.h>

// Behold, a zeroton!
class AbilityReader {
    static std::map<std::string, std::function<std::shared_ptr<Ability>(AbilityIDType, EntityIDType)>> constructors_;
    static bool initialized_;
    static void LoadConstructors();
    static std::shared_ptr<Ability> Construct(AbilityIDType id, EntityIDType entity_id, std::string type);
public:
    static std::shared_ptr<Ability> Read(EntityIDType entity_id, std::shared_ptr<FormattedReader> reader);
};


#endif
