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
        // Kruskals Algorithm
        // 1. Assign each cell to its own set.
        // 2. Choose the pair of neighboring cells with the lowest cost passage between them.
        //    If multiple are found, choose randomly between them
        // 3. If the two cells belong to different sets, merge them.
        // 4. Repeat 2 and 3 until only a single set remains.
         class kruskal : public IGenerator
         {
		 public:
            void apply(grid* grid) override final;
		 };
    }
}