#ifndef TRTS_MOVE_ABILITY_H
#define TRTS_MOVE_ABILITY_H

#include <ability.h>

class MoveAbility : public Ability {
protected:
    double speed_;

    class MoveCommand : public Command {
    public:
        double target_x_, target_y_;
        MoveCommand(AbilityIDType ability_id, double target_x, double target_y);
        explicit MoveCommand(AbilityIDType ability_id);
        void ReadInternals(std::shared_ptr<FormattedReader> reader) final;
        void WriteInternals(std::shared_ptr<FormattedWriter> writer) const final;
    };

public:
    static std::string type_;
    MoveAbility(AbilityIDType id, EntityIDType entity_id);
    std::shared_ptr<MoveCommand> MakeCommand(double target_x, double target_y);

    double GetSpeed() const;

    void ReadInternals(std::shared_ptr<FormattedReader> reader) final;
    void WriteInternals(std::shared_ptr<FormattedWriter> writer) const final;
    std::string TypeString() const override;
};

#endif
