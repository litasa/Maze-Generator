
#include <sstream>
#include <iostream>
#include <fstream>

#include <io.h>    // for _setmode()
#include <fcntl.h> // for _O_U16TEXT

#include "../core/maze_generation.h"

namespace maze
{
    namespace io
    {
        void print_to_console(grid* grid);
        void save_as_txt(grid* grid, const char* path);

        std::wstringstream grid_to_utf8(grid* grid);

        namespace helper
        {
            std::wstring determine_corner_utf8(cell* current, cell* east, cell* south, cell* south_east);
        }
    }
}