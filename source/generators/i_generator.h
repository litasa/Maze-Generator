#pragma once
#include <memory>
#include "../io/io.h"
namespace maze
{
	//Forward declerations
	class grid;
}

namespace maze
{
	namespace generator
	{
		class IGenerator
		{
		public:
			IGenerator(std::unique_ptr<grid> grid) : _grid(std::move(grid)) {}
			virtual ~IGenerator() = 0 {};

			virtual void generate_grid() = 0;

			void print_to_console()
			{
				io::print_to_console(_grid.get());
			}

		protected:
			std::unique_ptr<grid> _grid;
		};
	}
}
