#ifndef TRTS_ABILITY_H
#define TRTS_ABILITY_H

#include <memory>
#include <formatted_reader.h>
#include <formatted_writer.h>
#include <map>
#include <command.h>
#include <functional>
#include <id_types.h>

class Ability {
protected:
    AbilityIDType id_;
    EntityIDType entity_id_;
    Ability(AbilityIDType id, EntityIDType entity_id);
public:
    virtual void ReadInternals(std::shared_ptr<FormattedReader> reader) = 0;
    virtual void WriteInternals(std::shared_ptr<FormattedWriter> writer) const = 0;
    virtual std::string TypeString() const = 0;
    void Write(std::shared_ptr<FormattedWriter> writer) const;
};

#endif
