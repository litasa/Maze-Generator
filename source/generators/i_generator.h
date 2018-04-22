#pragma once

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
			IGenerator() {}
			virtual ~IGenerator() = 0;

			virtual void apply(grid* grid) = 0;
			virtual void apply(grid* grid, unsigned& num_steps) { /*Unimplemented return value somehow*/ }
		};
	}
}
