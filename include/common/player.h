#ifndef TRTS_PLAYER_H
#define TRTS_PLAYER_H

#include <istream>
#include <memory>
#include <formatted_reader.h>
#include <formatted_writer.h>

class Player {
public:
    Player();
    void Read(std::shared_ptr<FormattedReader> reader);
    void Write(std::shared_ptr<FormattedWriter> writer) const;
};

#endif
