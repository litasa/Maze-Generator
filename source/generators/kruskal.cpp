#include "kruskal.h"

namespace maze
{
    namespace kruskal
    {
        void apply(grid* grid)
        {
            std::vector<std::pair<cell*, cell*>> neighbours;
            std::unordered_map<cell*, unsigned> set_for_cell;
            std::unordered_map<unsigned, std::vector<cell*>> cells_in_set;

            //initialize
            for (unsigned row = 0; row < grid->number_of_rows(); ++row)
            {
                for (unsigned collumn = 0; collumn < grid->number_of_collumns(); ++collumn)
                {
                    unsigned set = (unsigned)set_for_cell.size();
                    cell* current_cell = grid->get_cell(row, collumn);
                    set_for_cell[current_cell] = set;
                    cells_in_set[set].push_back(current_cell);

                    if (current_cell->_neighbours[dir::SOUTH])
                    {
                        neighbours.push_back(std::make_pair(current_cell, current_cell->_neighbours[dir::SOUTH]));
                    }
                    if (current_cell->_neighbours[dir::EAST])
                    {
                        neighbours.push_back(std::make_pair(current_cell, current_cell->_neighbours[dir::EAST]));
                    }
                }
            }

            //two small helper functions
            auto can_merge = [&](cell* left, cell* right) { return set_for_cell[left] != set_for_cell[right]; };

            auto merge = [&](cell* left, cell* right)
            {
                left->link_with(right);

                unsigned winner = set_for_cell[left];
                unsigned looser = set_for_cell[right];
                std::vector<cell*> loosers = cells_in_set[looser];
                if (loosers.size() == 0) { loosers.push_back(right); }

                for (auto cell : loosers)
                {
                    cells_in_set[winner].push_back(cell);
                    set_for_cell[cell] = winner;
                }

                cells_in_set.erase(looser);
            };

            //The generation algorithm here
            unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(neighbours.begin(), neighbours.end(), std::default_random_engine(seed));
            while (neighbours.size() > 0)
            {
                std::pair<cell*, cell*> pair = neighbours.back();
                neighbours.pop_back();
                if (can_merge(pair.first, pair.second))
                {
                    merge(pair.first, pair.second);
                }
            }
        }
    }
}