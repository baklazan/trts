#ifndef TRTS_TARGETABLE_ABILITY_H
#define TRTS_TARGETABLE_ABILITY_H

#include <memory>
#include <target.h>
#include <task.h>
#include <multisearchable.h>

class TargetableAbility : public MultiSearchable<TargetableAbility> {
public:
    TargetableAbility(AbilityIDType id, EntityIDType entity_id);
    virtual bool WantsGroundTarget(const GroundTarget *target) = 0;
    virtual bool WantsEntityTarget(const EntityTarget *target) = 0;
    virtual std::shared_ptr<Task> ConsumeGroundTarget(const GroundTarget *target) = 0;
    virtual std::shared_ptr<Task> ConsumeEntityTarget(const EntityTarget *target) = 0;
};

#endif
