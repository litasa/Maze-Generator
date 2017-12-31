#include "kruskal.h"

namespace maze
{
    // Kruskals Algorithm
    // 1. Assign each cell to its own set.
    // 2. Choose the pair of neighboring cells with the lowest cost passage between them.
    //    If multiple are found, choose randomly between them
    // 3. If the two cells belong to different sets, merge them.
    // 4. Repeat 2 and 3 until only a single set remains.
    namespace kruskal
    {
        void apply(grid* grid)
        {
            //vector of neighbours south or east from current
            std::vector<std::pair<cell*, cell*>> neighbours;
            std::unordered_map<cell*, unsigned> set_for_cell;
            std::unordered_map<unsigned, std::vector<cell*>> cells_in_set;

            //initialize the sets and neighbours
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

            //two small helper functions used in the algorithm
            auto can_merge = [&set_for_cell](std::pair<cell*, cell*>& pair)
            {
                cell* current = pair.first;
                cell* south_or_east = pair.second;
                return set_for_cell[current] != set_for_cell[south_or_east];
            };

            auto merge = [&set_for_cell, &cells_in_set](std::pair<cell*, cell*>& pair)
            {
                cell* current = pair.first;
                cell* south_or_east = pair.second;
                current->link_with(south_or_east);

                unsigned winner = set_for_cell[current];
                unsigned looser = set_for_cell[south_or_east];
                std::vector<cell*> loosers = cells_in_set[looser];
                if (loosers.size() == 0) { loosers.push_back(south_or_east); }

                for (auto cell : loosers)
                {
                    cells_in_set[winner].push_back(cell);
                    set_for_cell[cell] = winner;
                }

                cells_in_set.erase(looser);
            };

            // Generation happens here.
            // Since the passage cost is the same, randomize the neighbours vector and loop over it
            unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(neighbours.begin(), neighbours.end(), std::default_random_engine(seed));
            while (neighbours.size() > 0)
            {
                std::pair<cell*, cell*> pair = neighbours.back();
                neighbours.pop_back();
                if (can_merge(pair))
                {
                    merge(pair);
                }
            }
        }
    }
}