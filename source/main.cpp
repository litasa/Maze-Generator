#include <iostream>

#include "core\grid.h"
#include "io\io.h"
#include "generators\kruskal.h"
#include "generators\sidewinder.h"
#include "generators\binary_tree.h"
#include "generators\aldous_broder.h"
#include "generators\wilsons.h"

#include "solvers\dijkstras.h"

void problem(unsigned line)
{
    std::wcout << "Problem at : " << line << std::endl;
}

int main()
{
    using namespace maze;
    int width, height;
    width = height = 10;
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
    io::print_to_console(&g);

	maze::generator::aldous_broder generator(std::make_unique<grid>(width,height));

	generator.generate_grid();
	generator.print_to_console();

    //maze::generator::binary_tree::apply(&g);
    //maze::generator::sidewinder::apply(&g);
    //maze::generator::kruskal::apply(&g);
    //unsigned steps = 0;
    //maze::generator::wilsons::apply(&g, steps);
    ////maze::generator::aldous_broder::apply(&g, steps);
    //std::cout << "Num steps before converging: " << steps << std::endl;
    //io::print_to_console(&g);
    //solver::dijkstras::dijkstras_result ret = maze::solver::dijkstras::shortest_path(&g);
    //std::vector<maze::cell*> shortest_path = maze::solver::dijkstras::reconstruct_path(ret);
    //io::print_shortest_path(shortest_path);
    //io::save_as_txt(&g, "test.txt");

    std::cin.get();
}