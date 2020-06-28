#ifndef TRTS_MOVE_TASK_H
#define TRTS_MOVE_TASK_H

#include <task.h>

class MoveTask : public Task {
private:
    double target_x_, target_y_, target_distance_;

public:
    MoveTask(EntityIDType entity_id, double target_x, double target_y, double target_distance);
    bool IsFinished() override;
    std::shared_ptr<Command> NextCommand() override;
};

#endif
