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
			wilsons(std::unique_ptr<grid> grid) : IGenerator(std::move(grid)) {}
			virtual ~wilsons() {}

			virtual void generate_grid() override final;

            static void apply(grid& grid, unsigned& steps);
		};
    }
}