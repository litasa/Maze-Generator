#include "aldous_broder.h"

#include "../core/grid.h"
#include "../core/cell.h"
#include "../math/probability.h"
namespace maze
{
namespace generator
{
namespace aldous_broder
{
    void apply(grid* grid, unsigned& num_steps)
    {
        unsigned rows = grid->number_of_rows();
        unsigned collumns = grid->number_of_collumns();

        unsigned startRow = math::probability::random_number(0, rows - 1);
        unsigned startCollumn = math::probability::random_number(0, collumns - 1);

        unsigned num_unvisited = grid->number_of_cells() - 1;

        cell* current = grid->get_cell(startRow, startCollumn);

        while (num_unvisited > 0)
        {
            cell* neighbour = nullptr;
            dir random;
            do
            {
                random = (dir)math::probability::random_number(0, 3);
                neighbour = current->get_neighbour(random);
            } while (neighbour == nullptr);
            
            if (neighbour->_links.empty())
            {
                current->link_with(random);
                num_unvisited--;
            }

            current = neighbour;
            num_steps++;
        }
    }
} //namespace aldous_broder
} //namespace generator
} //namespace maze