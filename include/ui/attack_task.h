#ifndef TRTS_ATTACK_TASK_H
#define TRTS_ATTACK_TASK_H

#include <task.h>

class AttackTask : public Task {
    EntityIDType target_entity_id_;
public:
    AttackTask(EntityIDType entity_id, EntityIDType target_entity_id);
    bool IsFinished() override;
    std::shared_ptr<Command> NextCommand() override;
};

#endif
