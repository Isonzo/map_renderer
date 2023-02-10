#include <raylib.h>
#include "rapidcsv.h"
#include <queue>
#include <vector>
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
        rapidcsv::Document map_data;
        std::vector<std::string> column_names;
        std::vector<Position> id_coords;

        void SetPixelColor(const int x, const int y, const Color color);
        void SetStart(const int x, const int y);
        bool IsInsideColor(const Color color);
        bool InBounds(const int x, const int y);
        bool InBounds(const Position pos);
        void ReadCoords();
        void Fill(const int x, const int y, const Color color);

    public:
        Map(std::string image_path, std::string data_path);
        ~Map() = default;
        void GenerateAll();
        Image& GetMapImage(){ return map_image; }
        void Export(const std::string filename);
        void ColorColumn(const std::string column_name);
};
