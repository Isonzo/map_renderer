#include "../include/map_generator.hpp"
#include <raylib.h>


Map::Map(std::string file_path)
{
    map_image = LoadImage(file_path.c_str());
}


void Map::SetPixelColor(int x, int y, Color color)
{
    if (!InBounds(x, y)) return;
    
    positions.push(Position{x, y});

    while (!positions.empty())
    {
        Position current_pos = positions.front();
        positions.pop();
        if (!IsInsideColor(GetImageColor(map_image, current_pos.x, current_pos.y))) continue;

        ImageDrawPixel(&map_image, current_pos.x, current_pos.y, color);

        // Queue up other cardinal directions
        Position up_dir { current_pos.x, current_pos.y - 1 };
        Position down_dir { current_pos.x, current_pos.y + 1 };
        Position left_dir { current_pos.x - 1, current_pos.y };
        Position right_dir { current_pos.x + 1, current_pos.y };

        if (InBounds(up_dir) && IsInsideColor(GetImageColor(map_image, up_dir.x, up_dir.y)))
            positions.push(up_dir);

        if (InBounds(down_dir) && IsInsideColor(GetImageColor(map_image, down_dir.x, down_dir.y)))
            positions.push(down_dir);

        if (InBounds(left_dir) && IsInsideColor(GetImageColor(map_image, left_dir.x, left_dir.y)))
            positions.push(left_dir);

        if (InBounds(right_dir) && IsInsideColor(GetImageColor(map_image, right_dir.x, right_dir.y)))
            positions.push(right_dir);
    }

}


void Map::SetStart(int x, int y)
{
    inside_color = GetImageColor(map_image, x, y);
}


bool Map::IsInsideColor(Color color)
{
    return color.r == inside_color.r && color.g == inside_color.g && color.b == inside_color.b;// && color.a == inside_color.a;
}


void Map::Fill(int x, int y, Color color)
{
    SetStart(x, y);
    SetPixelColor(x, y, color);
}


void Map::Export(std::string filename)
{
    ExportImage(map_image, filename.c_str());
}


bool Map::InBounds(int x, int y)
{
    if (x < 0 || y < 0 || x >= map_image.width || y >= map_image.height) return false;
    return true;
}


bool Map::InBounds(Position pos)
{
    if (pos.x < 0 || pos.y < 0 || pos.x >= map_image.width || pos.y >= map_image.height) return false;
    return true;
}
