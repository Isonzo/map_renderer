#include "../include/rapidcsv.h"
#include "../include/map_generator.hpp"
#include <raylib.h>
#include <vector>

int main(void)
{
    Map map("test_map.png");

    map.Fill(900, 630, BLUE);
    map.Fill(1000, 250, GREEN);
    map.Fill(1250, 600, RED);
    map.Fill(700, 300, YELLOW);

    map.Export("result.png");
}
