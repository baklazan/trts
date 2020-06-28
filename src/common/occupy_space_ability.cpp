#include <occupy_space_ability.h>

std::string OccupySpaceAbility::type_ = "occupy_space";

std::string OccupySpaceAbility::TypeString() const {
    return type_;
}

void OccupySpaceAbility::ReadInternals(std::shared_ptr<FormattedReader> reader) {
    reader->Comment("x=");
    x_ = reader->Double();
    reader->MinorSeparator();

    reader->Comment("y=");
    y_ = reader->Double();
    reader->MinorSeparator();

    reader->Comment("r=");
    radius_ = reader->Double();
}

OccupySpaceAbility::OccupySpaceAbility(AbilityIDType id, EntityIDType entity_id) : Ability(id, entity_id), Searchable<OccupySpaceAbility>(entity_id) {
}

void OccupySpaceAbility::WriteInternals(std::shared_ptr<FormattedWriter> writer) const {
    writer->Comment("x=");
    writer->Double(x_);
    writer->MinorSeparator();

    writer->Comment("y=");
    writer->Double(y_);
    writer->MinorSeparator();

    writer->Comment("r=");
    writer->Double(radius_);
}

double OccupySpaceAbility::GetX() const {
    return x_;
}


double OccupySpaceAbility::GetY() const {
    return y_;
}

double OccupySpaceAbility::GetRadius() const {
    return radius_;
}

void OccupySpaceAbility::ChangePosition(double new_x, double new_y) {
    x_ = new_x;
    y_ = new_y;
}

bool OccupySpaceAbility::ContainsPoint(double x, double y) {
    double dx = x - x_, dy = y - y_;
    return dx * dx + dy * dy <= radius_ * radius_;
}

std::vector<EntityIDType> OccupySpaceAbility::EntitiesAtPoint(double x, double y) {
    std::vector<EntityIDType> result;
    for (const auto &item : by_index_) {
        OccupySpaceAbility *ability = item.second;
        if (ability->ContainsPoint(x, y)) {
            result.push_back(ability->entity_id_);
        }
    }
    return result;
}

