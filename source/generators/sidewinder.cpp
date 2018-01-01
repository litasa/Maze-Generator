#include "sidewinder.h"

#include "../math/probability.h"
#include "../core/grid.h"
#include "../core/cell.h"

namespace maze
{
    // Sidewinder Algorithm
    // For each cell in a row:
    // 1. Flip a coin.
    //    True:  Link and move east. Add cell to current run
    //    False: Take a random cell in run and link it north. Reset run. Move east
    // 2. If unable to link east. Reset run and link north.
    namespace sidewinder
    {
        void apply(grid* grid)
        {
            for (unsigned row = 0; row < grid->number_of_rows(); ++row)
            {
                std::vector<cell*> run;
                for (unsigned collumn = 0; collumn < grid->number_of_collumns(); ++collumn)
                {
                    cell* current_cell = grid->get_cell(row, collumn);

                    run.push_back(current_cell);

                    bool move_east = math::probability::flip_coin();
                    bool at_eastern_boundary = current_cell->east() == nullptr;
                    bool at_southern_boundary = current_cell->south() == nullptr;

                    if (at_southern_boundary || (move_east && !at_eastern_boundary))
                    {
                        current_cell->link_with(dir::EAST);
                        run.push_back(current_cell);
                    }
                    else
                    {
                        run[math::probability::random_number(0,run.size() -1)]->link_with(dir::SOUTH);
                        run.clear();
                    }
                }
            }
        }
    }
}