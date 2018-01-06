#include "dijkstras.h"

#include "../core/grid.h"
#include "../core/cell.h"
#include <queue>
#include <functional> //std::greater

namespace maze
{
    namespace solver
    {
        namespace dijkstras
        {
            dijkstras_result shortest_path(grid* grid)
            {
                // TODO: Add start and stop location. Now assume topleft corner and bottomright
                cell* start = grid->get_cell(0, 0);
                cell* stop = grid->get_cell(grid->number_of_rows() - 1, grid->number_of_collumns() - 1);
                std::unordered_map<cell*, cell*> came_from;
                std::unordered_map<cell*, unsigned> cost_map; //cost from start to current cell

                //make the priority queue a min heap of cell to cost pair 
                std::priority_queue<
                    std::pair<unsigned,cell*>,
                    std::vector<std::pair<unsigned, cell*>>,
                    std::greater<std::pair<unsigned,cell*>>
                > frontier;

                //two small convenience functions for nicer syntax
                auto add_to_frontier = [&frontier](cell* cell,unsigned cost) {
                    frontier.emplace(cost, cell);
                };

                auto get_shortest_distance_traveled_in_frontier = [&frontier]() {
                    cell* cell = frontier.top().second;
                    frontier.pop();
                    return cell;
                };

                //Setup data
                add_to_frontier(start, 0);
                came_from[start] = start;
                cost_map[start] = 0;

                while (!frontier.empty())
                {
                    cell* current = get_shortest_distance_traveled_in_frontier();
                    if (current == stop)
                    {
                        break;
                    }
                    for each (cell* link in current->_links)
                    {
                        // TODO: The +1 should be changed so we can have variable cost for each link
                        unsigned new_cost = cost_map[current] + 1;
                        if (!cost_map.count(link) || new_cost < cost_map[link])
                        {
                            cost_map[link] = new_cost;
                            came_from[link] = current;
                            add_to_frontier(link, new_cost);
                        }
                    }
                }

                dijkstras_result result;
                result.cost_mapping = std::move(cost_map);
                result.path_mapping = std::move(came_from);
                result.start = start;
                result.end = stop;

                return result;
            }

            std::vector<cell*> reconstruct_path(dijkstras_result& given_result)
            {
                std::vector<cell*> path;
                cell* current = given_result.end;
                while (current != given_result.start)
                {
                    path.push_back(current);
                    current = given_result.path_mapping[current];
                }
                path.push_back(given_result.start);
                std::reverse(path.begin(), path.end());
                return path;
            }
        } //namespace dijkstras
    } //namespace solver
} //namespace maze