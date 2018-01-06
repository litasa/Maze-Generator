#include <unordered_map>
//forward decleration
namespace maze
{
    class grid;
    struct cell;
}
namespace maze
{
    namespace solver
    {
        namespace dijkstras
        {
            struct dijkstras_result
            {
                cell* start;
                cell* end;
                std::unordered_map<cell*, unsigned> cost_mapping;
                std::unordered_map<cell*, cell*> path_mapping;
            };

            dijkstras_result shortest_path(grid* grid);

            std::vector<cell*> reconstruct_path(dijkstras_result& given_result);
        }
    }
}