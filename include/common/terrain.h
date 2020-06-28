#ifndef TRTS_TERRAIN_H
#define TRTS_TERRAIN_H

#include <istream>
#include <vector>
#include <memory>
#include <formatted_reader.h>
#include <formatted_writer.h>

enum Tile {TILE_FLAT = 0, TILE_WATER = 1};

void WriteTile(const Tile &tile, std::shared_ptr<FormattedWriter> &writer);
Tile ReadTile(std::shared_ptr<FormattedReader> &reader);

class Terrain {
public:
    int width_, height_;
    std::vector<std::vector<Tile>> tiles_;
    Terrain();
    void Read(std::shared_ptr<FormattedReader> reader);
    void Write(std::shared_ptr<FormattedWriter> writer) const;
};

#endif
