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
        class wilsons : public IGenerator
        {
		public:
            void apply(grid* grid, unsigned& steps) override final;
		};
    }
}