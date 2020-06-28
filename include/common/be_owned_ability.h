#ifndef TRTS_BE_OWNED_ABILITY_H
#define TRTS_BE_OWNED_ABILITY_H

#include <ability.h>
#include <searchable.h>

class BeOwnedAbility : public Ability, public Searchable<BeOwnedAbility> {
protected:
    PlayerIDType owner_id_;
public:
    BeOwnedAbility(AbilityIDType id, EntityIDType entity_id);

    static std::string type_;
    void ReadInternals(std::shared_ptr<FormattedReader> reader) final;
    void WriteInternals(std::shared_ptr<FormattedWriter> writer) const final;
    std::string TypeString() const;

    PlayerIDType GetOwnerId() const;
};

#endif
