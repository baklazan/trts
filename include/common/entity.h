#ifndef TRTS_ENTITY_H
#define TRTS_ENTITY_H

#include <string>
#include <istream>
#include <formatted_reader.h>
#include <formatted_writer.h>
#include <memory>
#include <ability.h>
#include <vector>
#include <id_types.h>


class Entity {
public:
    EntityIDType id_;
    std::vector<std::shared_ptr<Ability>> abilities_;
    Entity();
    void Read(std::shared_ptr<FormattedReader> reader);
    void Write(std::shared_ptr<FormattedWriter> writer) const;
};

#endif
