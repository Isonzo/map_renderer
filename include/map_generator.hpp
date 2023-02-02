#include <raylib.h>
#include "rapidcsv.h"
#include <queue>
#pragma once

struct Position
{
    int x, y;
};


class Map
{
    private:
        Image map_image;
        Color inside_color;
        std::queue<Position> positions;

    public:
        Map(std::string file_path);
        void SetPixelColor(int x, int y, Color color);
        void SetStart(int x, int y);
        bool IsInsideColor(Color color);
        void Fill(int x, int y, Color color);
        void Export(std::string filename);
        Image& GetMapImage(){ return map_image; }
        bool InBounds(int x, int y);
        bool InBounds(Position pos);
};
