#ifndef TRTS_OCCUPY_SPACE_H
#define TRTS_OCCUPY_SPACE_ABILITY_H

#include <ability.h>
#include <searchable.h>
#include <vector>

class OccupySpaceAbility : public Ability, public Searchable<OccupySpaceAbility> {
    double x_, y_, radius_;
public:
    double GetX() const;
    double GetY() const;
    double GetRadius() const;


    void ChangePosition(double new_x, double new_y);

    static std::vector<EntityIDType> EntitiesAtPoint(double x, double y);
    static std::string type_;
    OccupySpaceAbility(AbilityIDType id, EntityIDType entity_id);

    bool ContainsPoint(double x, double y);

    void ReadInternals(std::shared_ptr<FormattedReader> reader) final;
    void WriteInternals(std::shared_ptr<FormattedWriter> writer) const final;
    std::string TypeString() const override;
};

#endif
