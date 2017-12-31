#include "maze_generation.h"

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
				delete _grid[row][collumn];
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
		return _grid[row][collumn];
	}
	
	//private functions
	void grid::setup_cells()
	{
		for (uint32_t row = 0; row < _rows; ++row)
		{
			for (uint32_t collumn = 0; collumn < _collumns; ++collumn)
			{
				_grid[row][collumn]->_neighbours[dir::NORTH] = get_cell(row - 1, collumn);
				_grid[row][collumn]->_neighbours[dir::SOUTH] = get_cell(row + 1, collumn);
				_grid[row][collumn]->_neighbours[dir::WEST] = get_cell(row, collumn - 1);
				_grid[row][collumn]->_neighbours[dir::EAST] = get_cell(row, collumn + 1);
			}
		}
	}
	void grid::initialize()
	{
		_grid.resize(_collumns, std::vector<cell*>(_rows, nullptr));
		for (uint32_t row = 0; row < _rows; ++row)
		{
			for (uint32_t collumn = 0; collumn < _collumns; ++collumn)
			{
				_grid[row][collumn] = new cell(row, collumn);
			}
		}
	}
}