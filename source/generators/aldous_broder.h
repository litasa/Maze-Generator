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
			 void apply(grid* grid) override final;
             void apply(grid* grid, unsigned& num_steps) override final;
		 };
    }
}