#ifndef TRTS_TARGET_H
#define TRTS_TARGET_H

#include <vector>
#include <memory>
#include <ui_state.h>
#include <task.h>

class TargetableAbility;

class Target {
public:
    virtual void GetSelected(std::shared_ptr<UIState> ui_state) const = 0;
    virtual bool IsWanted(TargetableAbility *ability) const = 0;
    virtual std::shared_ptr<Task> BeConsumed(TargetableAbility *ability) const = 0;
};

class EntityTarget : public Target {
public:
    EntityIDType entity_id_;
    explicit EntityTarget(EntityIDType entity_id);
    void GetSelected(std::shared_ptr<UIState> ui_state) const override;
    bool IsWanted(TargetableAbility *ability) const override;
    std::shared_ptr<Task> BeConsumed(TargetableAbility *ability) const override;
};

class GroundTarget : public Target {
public:
    double x_, y_;
    GroundTarget(double x, double y);
    void GetSelected(std::shared_ptr<UIState> ui_state) const override;
    bool IsWanted(TargetableAbility *ability) const override;
    std::shared_ptr<Task> BeConsumed(TargetableAbility *ability) const override;
};

class TargetPicker {
    std::vector<std::vector<EntityIDType>> target_map_;
    double left_x_, top_y_, tile_size_;
public:
    TargetPicker(std::vector<std::vector<EntityIDType>> target_map, double left_x, double top_y, double tile_size);
    std::shared_ptr<Target> PickTarget(int x, int y);
};



#endif
