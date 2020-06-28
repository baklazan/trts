#ifndef TRTS_ATTACK_ABILITY_H
#define TRTS_ATTACK_ABILITY_H

#include <ability.h>

class AttackAbility : public Ability {
protected:
    int damage_;
    double range_;

    class AttackCommand : public Command {
    public:
        double target_x_, target_y_;
        explicit AttackCommand(AbilityIDType ability_id);
        AttackCommand(AbilityIDType ability_id, double target_x, double target_y);

        void ReadInternals(std::shared_ptr<FormattedReader> reader) final;
        void WriteInternals(std::shared_ptr<FormattedWriter> writer) const final;
    };
public:
    double GetRange() const;
    int GetDamage() const;

    static std::string type_;
    AttackAbility(AbilityIDType id, EntityIDType entity_id);
    void ReadInternals(std::shared_ptr<FormattedReader> reader) final;
    void WriteInternals(std::shared_ptr<FormattedWriter> writer) const final;
    std::string TypeString() const override;

    std::shared_ptr<AttackCommand> MakeCommand(double target_x, double target_y);
};

#endif
