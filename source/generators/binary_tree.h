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
        // Binary Tree Algorithm
        // For every cell flip a coin
        // If true we want to link north
        // Else we want to link east
        class binary_tree : public IGenerator
        {
		public:
            void apply(grid* grid) override final;
		};
    }
}