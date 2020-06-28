#ifndef TRTS_TASK_H
#define TRTS_TASK_H

#include <memory>
#include <command.h>

class Task {

public:
    explicit Task(EntityIDType entity_id);
    EntityIDType entity_id_;
    virtual bool IsFinished() = 0;
    virtual std::shared_ptr<Command> NextCommand() = 0;
};

#endif
