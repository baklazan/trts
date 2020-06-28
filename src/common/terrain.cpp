#include <terrain.h>
#include <iostream>

Terrain::Terrain() = default;

void WriteTile(const Tile &tile, std::shared_ptr<FormattedWriter> &writer) {
    writer->Int(static_cast<int32_t>(tile));
}

Tile ReadTile(std::shared_ptr<FormattedReader> &reader) {
    return static_cast<Tile>(reader->Int());
}

void Terrain::Write(std::shared_ptr<FormattedWriter> writer) const {
    writer->Comment("width=");
    writer->Int(width_);
    writer->MinorSeparator();
    writer->Comment("height=");
    writer->Int(height_);
    writer->MajorSeparator();
    writer->EnterBlock();
    for (int y=0; y<height_; y++) {
        for (int x=0; x<width_; x++) {
            WriteTile(tiles_[y][x], writer);
            if (x + 1 < width_) writer->MinorSeparator();
        }
        writer->MajorSeparator();
    }
    writer->EscapeBlock();
}

void Terrain::Read(std::shared_ptr<FormattedReader> reader) {
    reader->Comment("width=");
    width_ = reader->Int();
    reader->MinorSeparator();
    reader->Comment("height=");
    height_ = reader->Int();
    reader->MajorSeparator();
    reader->EnterBlock();

    tiles_.resize(height_, std::vector<Tile> (width_));
    for (int y=0; y<height_; y++) {
        for (int x=0; x<width_; x++) {
            tiles_[y][x] = ReadTile(reader);
            if (x + 1 < width_) reader->MinorSeparator();
        }
        reader->MajorSeparator();
    }
    reader->EscapeBlock();
}
