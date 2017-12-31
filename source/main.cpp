#include <iostream>

#include "core/maze_generation.h"
#include "io\io.h"
#include "generators/kruskal.h"
#include "generators\sidewinder.h"

void problem(unsigned line)
{
    std::wcout << "Problem at : " << line << std::endl;
}

int main()
{
    int width, height;
    width = height = 15;
    maze::grid g(width, height);

    /*************
    Testing to get cell outside of grid
    **************/
        //outside to left
        if (g.get_cell(-1, 0) != nullptr) { problem(__LINE__); }
        //outside to right
        if (g.get_cell(width + 1, 0) != nullptr) { problem(__LINE__); }
        //outside above
        if (g.get_cell(0, -1) != nullptr) { problem(__LINE__); }
        //outside below
        if (g.get_cell(0, height + 1) != nullptr) { problem(__LINE__); }
    maze::io::print_to_console(&g);

    maze::sidewinder::apply(&g);
    //maze::kruskal::apply(&g);

    maze::io::print_to_console(&g);
    maze::io::save_as_txt(&g, "test.txt");

    std::cin.get();
}