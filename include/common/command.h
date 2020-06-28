#ifndef TRTS_COMMAND_H
#define TRTS_COMMAND_H

#include <memory>
#include <formatted_reader.h>
#include <formatted_writer.h>
#include <id_types.h>

class Command {
    AbilityIDType ability_id_;
protected:
    explicit Command(AbilityIDType ability_id);
public:
    virtual void ReadInternals(std::shared_ptr<FormattedReader> reader) = 0;
    virtual void WriteInternals(std::shared_ptr<FormattedWriter> writer) const = 0;
    void Write(std::shared_ptr<FormattedWriter> writer) const;
};

#endif
