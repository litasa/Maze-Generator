#pragma once
#include <sstream>
#include <vector>


//forward include
namespace maze
{
    struct cell;
    class grid;
}

namespace maze
{
    namespace io
    {
        void print_to_console(grid* grid);
        void save_as_txt(grid* grid, const char* path);

        std::wstringstream grid_to_utf8(grid* grid);
        std::wstring determine_corner_utf8(cell* current, cell* east, cell* south, cell* south_east);

        // Returns a string with (x,y) coordinates from top left corner.
        std::string toString(cell* cell);

        void print_shortest_path(std::vector<cell*>& vec);
    }
}