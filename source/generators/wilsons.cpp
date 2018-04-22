#pragma once
#include "wilsons.h"

#include <unordered_map>

#include "../core/cell.h"
#include "../core/grid.h"
#include "../math/probability.h"

namespace maze
{
namespace generator
{
	void wilsons::generate_grid()
	{
		unsigned temp = 0;
		apply(*_grid, temp);
	}

	void wilsons::apply(grid& grid, unsigned& steps)
    {
        unsigned start_pos = 0;
        unsigned end_pos = 0;
        do
        {
            start_pos = math::probability::random_number(0, grid.number_of_cells() - 1);
            end_pos = math::probability::random_number(0, grid.number_of_cells() - 1);
        } while (start_pos == end_pos);

        cell* start = grid.get_cell(start_pos);
        cell* end = grid.get_cell(end_pos);

        std::unordered_map<cell*, cell*> marked_cells;
        marked_cells.reserve(grid.number_of_cells()); //know size will not exceed current number of cells
        marked_cells[end] = nullptr;
        
        std::vector<cell*> current_path;
        current_path.reserve(grid.number_of_cells()); //know size will not exceed current number of cells
        current_path.push_back(start);

        auto random_step_dir = []() {
            return (maze::dir)math::probability::random_number(0, 3);
        };
        // looking from the back since it is highly likely that the loop is formed with the last added item
        auto part_of_current_path = [&current_path](cell* item) {
            return std::find(current_path.rbegin(), current_path.rend(), item);
        };

        cell* current = start;
        while (marked_cells.size() < grid.number_of_cells())
        {
            steps++;
            // take random step
            dir stepping_dir = random_step_dir();
            cell* next_step = current->get_neighbour(stepping_dir);
            if (next_step == nullptr) //if next step is invalid
            {
                continue;
            }

            auto found = part_of_current_path(next_step);
            if (found != current_path.rend()) //the next step IS part of the path
            {
                current_path.erase(found.base(), current_path.end());
                current = current_path.back();
                continue;
            }

            if (marked_cells.count(next_step)) //Cell is already visited
            {
                current_path.push_back(next_step);
                
                // carving path
                for (unsigned i = 0; i < current_path.size() - 1; ++i)
                {
                    current_path[i]->link_with(current_path[i + 1]);
                    marked_cells[current_path[i]];
                }

                // All cells visited
                if (marked_cells.size() == grid.number_of_cells())
                {
                    break;
                }
                current_path.clear();

                // pick new position to start from.
                while (marked_cells.count(current))
                {
                    current = grid.get_cell(math::probability::random_number(0, grid.number_of_cells() - 1));
                }
                current_path.push_back(current);
                continue;
            }

            current_path.push_back(next_step);
            current = next_step;
        }
        
    }
} //namespace generator
} //namespace maze