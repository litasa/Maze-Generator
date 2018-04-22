#pragma once
#include "i_generator.h"
//forward decleration
namespace maze
{
    class grid;
}

namespace maze
{
    namespace generator
    {
        // Sidewinder Algorithm
        // For each cell in a row:
        // 1. Flip a coin.
        //    True:  Link and move east. Add cell to current run
        //    False: Take a random cell in run and link it north. Reset run. Move east
        // 2. If unable to link east. Reset run and link north.
        class sidewinder : public IGenerator
        {
		public:
            void apply(grid* grid) override final;
		};
    }
}