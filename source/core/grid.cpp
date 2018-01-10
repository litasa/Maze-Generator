#include "grid.h"
#include "cell.h"

namespace maze
{
	//public functions
	grid::grid(uint32_t rows, uint32_t collumns) 
		: _rows(rows), _collumns(collumns)
	{
			initialize();
			setup_cells();
	}

	grid::~grid()
	{
		for (uint32_t row = 0; row < _rows; ++row)
		{
			for (uint32_t collumn = 0; collumn < _collumns; ++collumn)
			{
                const unsigned pos = row * _collumns + collumn;
                if (_grid[pos])
                {
                    delete _grid[pos];
                }
			}
		}
	}

	cell* grid::get_cell(int row, int collumn)
	{
		if (row >= (int)_rows || row < 0)
		{
			return nullptr;
		}
		if (collumn >= (int)_collumns || collumn < 0)
		{
			return nullptr;
		}
        const unsigned pos = row * _collumns + collumn;
		return _grid[pos];
	}

    cell * grid::get_cell(unsigned number)
    {
        return _grid[number];
    }
	
	//private functions
	void grid::setup_cells()
	{
		for (uint32_t row = 0; row < _rows; ++row)
		{
			for (uint32_t collumn = 0; collumn < _collumns; ++collumn)
			{
                const unsigned pos = row * _collumns + collumn;
				_grid[pos]->_neighbours[dir::NORTH] = get_cell(row - 1, collumn);
				_grid[pos]->_neighbours[dir::SOUTH] = get_cell(row + 1, collumn);
				_grid[pos]->_neighbours[dir::WEST] = get_cell(row, collumn - 1);
				_grid[pos]->_neighbours[dir::EAST] = get_cell(row, collumn + 1);
			}
		}
	}
	void grid::initialize()
	{
		_grid.resize(_collumns * _rows);
		for (uint32_t row = 0; row < _rows; ++row)
		{
			for (uint32_t collumn = 0; collumn < _collumns; ++collumn)
			{
                const unsigned pos = row * _collumns + collumn;
				_grid[pos] = new cell(row, collumn);
			}
		}
	}
}