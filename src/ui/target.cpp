#include <target.h>
#include <iostream>
#include <targetable_ability.h>

TargetPicker::TargetPicker(std::vector<std::vector<EntityIDType>> target_map, double left_x, double top_y, double tile_size)
        : target_map_(target_map), left_x_(left_x), top_y_(top_y), tile_size_(tile_size) {

}

std::shared_ptr<Target> TargetPicker::PickTarget(int x, int y) {
    std::cerr << "picking at [" << x << ", " << y << "]" << std::endl;
    std::cerr << target_map_.size() << std::endl;
    if (y < 0 || y >= target_map_.size() || x < 0 || x >= target_map_[y].size()) {
        return std::shared_ptr<Target>(nullptr);
    }
    if (target_map_[y][x] != kNoEntityId) {
        return std::make_shared<EntityTarget>(target_map_[y][x]);
    }
    else {
        return std::make_shared<GroundTarget>(left_x_ + x / tile_size_, top_y_ + y / tile_size_);
    }
}

EntityTarget::EntityTarget(EntityIDType entity_id) : entity_id_(entity_id) { }


void EntityTarget::GetSelected(std::shared_ptr<UIState> ui_state) const {
    ui_state->selected_entity_id_ = entity_id_;
}

bool EntityTarget::IsWanted(TargetableAbility *ability) const {
    return ability->WantsEntityTarget(this);
}

std::shared_ptr<Task> EntityTarget::BeConsumed(TargetableAbility *ability) const {
    return ability->ConsumeEntityTarget(this);
}


GroundTarget::GroundTarget(double x, double y) : x_(x), y_(y) { }

void GroundTarget::GetSelected(std::shared_ptr<UIState> ui_state) const {
    ui_state->selected_entity_id_ = kNoEntityId;
}

bool GroundTarget::IsWanted(TargetableAbility *ability) const {
    return ability->WantsGroundTarget(this);
}

std::shared_ptr<Task> GroundTarget::BeConsumed(TargetableAbility *ability) const {
    return ability->ConsumeGroundTarget(this);
}
