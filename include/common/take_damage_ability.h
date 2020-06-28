#ifndef TRTS_TAKE_DAMAGE_ABILITY_H
#define TRTS_TAKE_DAMAGE_ABILITY_H

#include <searchable.h>
#include <memory>
#include <formatted_writer.h>
#include <formatted_reader.h>
#include <ability.h>

class VulnerAbility : public Ability, public Searchable<VulnerAbility> {
protected:
    int health_, max_health_;
public:
    int GetHealth() const;
    int GetMaxHealth() const;

    void ReadInternals(std::shared_ptr<FormattedReader> reader) final;
    void WriteInternals(std::shared_ptr<FormattedWriter> writer) const final;
    std::string TypeString() const override;
    VulnerAbility(AbilityIDType id, EntityIDType entity_id);

    static std::string type_;
};

#endif
