#include "../include/rapidcsv.h"
#include "../include/map_generator.hpp"
#include <raylib.h>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Error: Missing required arguments!" << "\n";
        std::cerr << "Usage: mapgen <input_image> <input_data>" << "\n";

        return -1;
    }
    Map map(argv[1], argv[2]);

    map.GenerateAll();

    return 0;
}
