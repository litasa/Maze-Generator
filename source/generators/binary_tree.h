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
			binary_tree(std::unique_ptr<grid> grid) : IGenerator(std::move(grid)) {}
			virtual ~binary_tree() {}

			virtual void generate_grid() override final;

            static void apply(grid& grid);
		};
    }
}