#include "../include/map_generator.hpp"
#include "../include/rapidcsv.h"
#include <algorithm>
#include <raylib.h>
#include <string>
#include <vector>


Map::Map(std::string image_path, std::string data_path)
{
    map_image = LoadImage(image_path.c_str());
    map_data = rapidcsv::Document(data_path);
    column_names = map_data.GetColumnNames();

    std::erase_if(column_names, [](std::string x) { if (x == "x" || x == "y" || x == "ID") { return true;} return false;});

    ReadCoords();

    for (std::string name : column_names)
    {
        std::cout << name << "\n";
    }
}


void Map::GenerateAll()
{
    for (std::string column : column_names)
    {
        ColorColumn(column);
        Export(column + ".png");
    }
}


void Map::SetPixelColor(const int x, const int y, const Color color)
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


void Map::SetStart(const int x, const int y)
{
    inside_color = GetImageColor(map_image, x, y);
}


bool Map::IsInsideColor(const Color color)
{
    return color.r == inside_color.r && color.g == inside_color.g && color.b == inside_color.b;// && color.a == inside_color.a;
}


void Map::Fill(const int x, const int y, const Color color)
{
    SetStart(x, y);
    SetPixelColor(x, y, color);
}


void Map::Export(const std::string filename)
{
    ExportImage(map_image, filename.c_str());
}


void Map::ColorColumn(const std::string column_name)
{
    std::vector<float> column_data = map_data.GetColumn<float>(column_name);
    float max = *std::max_element(column_data.begin(), column_data.end());
    float min = *std::min_element(column_data.begin(), column_data.end());

    Color fill_color{50, 0, 0, 255};

    for(int i = 0; i < column_data.size(); i++)
    {
        float data = column_data[i];
        float percent = (data - min / max - min) * 100;

        fill_color.g = percent * 2;
        
        Fill(id_coords[i].x, id_coords[i].y, fill_color);
    }
}


bool Map::InBounds(const int x, const int y)
{
    if (x < 0 || y < 0 || x >= map_image.width || y >= map_image.height) return false;
    return true;
}


bool Map::InBounds(const Position pos)
{
    if (pos.x < 0 || pos.y < 0 || pos.x >= map_image.width || pos.y >= map_image.height) return false;
    return true;
}


void Map::ReadCoords()
{
    auto temp_x_pos = map_data.GetColumn<int>("x");
    auto temp_y_pos = map_data.GetColumn<int>("y");

    for (int i = 0; i < temp_x_pos.size(); i++)
    {
        Position new_pos {temp_x_pos[i], temp_y_pos[i]};
        id_coords.push_back(new_pos);
    }
}
