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
         class aldous_broder : public IGenerator
		 {
		 public:
			 aldous_broder(std::unique_ptr<grid> grid) : IGenerator(std::move(grid)) {}
			 virtual ~aldous_broder() {}

			 virtual void generate_grid() override final;

			 static void apply(grid& grid);
             static void apply(grid& grid, unsigned& num_steps);
		 };
    }
}