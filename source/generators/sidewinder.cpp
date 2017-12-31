#include "sidewinder.h"

#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

namespace maze
{
    namespace sidewinder
    {
        void apply(grid* grid)
        {
            unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine generator(seed);
            std::bernoulli_distribution distribution(0.5);
            
            for (int row = 0; row < grid->number_of_rows(); ++row)
            {
                std::vector<cell*> run;
                for (int collumn = 0; collumn < grid->number_of_collumns(); ++collumn)
                {
                    cell* current_cell = grid->get_cell(row, collumn);

                    run.push_back(current_cell);

                    bool move_east = distribution(generator);
                    bool at_eastern_boundary = current_cell->east() == nullptr;
                    bool at_southern_boundary = current_cell->south() == nullptr;

                    if (at_southern_boundary || (!at_eastern_boundary && move_east))
                    {
                        current_cell->link_with(dir::EAST);
                        run.push_back(current_cell);
                    }
                    else
                    {
                        std::uniform_int_distribution<int> dist(0, run.size() - 1);
                        run[dist(generator)]->link_with(dir::SOUTH);
                        run.clear();
                    }
                }
            }
        }
    }
}