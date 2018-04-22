#include "binary_tree.h"

#include "../math/probability.h"
#include "../core/grid.h"
#include "../core/cell.h"

namespace maze
{
    namespace generator
    {
		void binary_tree::generate_grid()
		{
			apply(*_grid);
		}

		void binary_tree::apply(grid& grid)
        {
            for (unsigned row = 0; row < grid.number_of_rows(); ++row)
            {
                for (unsigned collumn = 0; collumn < grid.number_of_collumns(); ++collumn)
                {
                    bool link_north = math::probability::flip_coin();
                    bool at_north_border = row == 0;
                    bool at_east_border = collumn == grid.number_of_collumns() - 1;

                    if (at_east_border || (!at_north_border && link_north))
                    {
                        grid.get_cell(row, collumn)->link_with(dir::NORTH);
                    }
                    else
                    {
                        grid.get_cell(row, collumn)->link_with(dir::EAST);
                    }
                }
            }
        }
    } //namespace generator
}//namespace maze