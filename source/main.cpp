#include <iostream>

#include "core\grid.h"
#include "io\io.h"
#include "generators\kruskal.h"
#include "generators\sidewinder.h"
#include "generators\binary_tree.h"

#include "solvers\dijkstras.h"

void problem(unsigned line)
{
    std::wcout << "Problem at : " << line << std::endl;
}

int main()
{
    int width, height;
    width = height = 5;
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

    //maze::generator::binary_tree::apply(&g);
    //maze::generator::sidewinder::apply(&g);
    maze::generator::kruskal::apply(&g);
    
    maze::io::print_to_console(&g);
    maze::solver::dijkstras::dijkstras_result ret = maze::solver::dijkstras::shortest_path(&g);
    std::vector<maze::cell*> shortest_path = maze::solver::dijkstras::reconstruct_path(ret);
    maze::io::print_shortest_path(shortest_path);
    maze::io::save_as_txt(&g, "test.txt");

    std::cin.get();
}