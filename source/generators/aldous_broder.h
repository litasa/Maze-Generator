#pragma once
//forward decleration
namespace maze
{
    class grid;
}

namespace maze
{
    namespace generator
    {
         namespace aldous_broder
        {
            void apply(grid* grid, unsigned& num_steps);
        }
    }
}