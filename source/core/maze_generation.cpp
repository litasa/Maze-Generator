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

	
	void grid::print_to_console()
	{
		//potential corners: ┌ ┐ └ ┘ ├ ┤ ┬ ┴ ┼ *

		//assumption. All outer edges are closed
		int prev_mode = _setmode(_fileno(stdout), _O_U16TEXT);
		std::wstringstream ss = grid_to_utf8();
		std::wcout << ss.str();
		_setmode(_fileno(stdout), prev_mode);
	}

	void grid::save_as_txt(const char* path)
	{
		std::wstringstream ss = grid_to_utf8();
		FILE *file;
		//file = fopen("test.txt", "w,ccs=UTF-8");
		fopen_s(&file, "test.txt", "w,ccs=UTF-8");
		fwprintf(file, ss.str().c_str());
		fclose(file);
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

	//void apply_kruskal(grid* grid)
	//{
	//	std::vector<std::pair<cell*, cell*>> neighbours;
	//	std::unordered_map<cell*, unsigned> set_for_cell;
	//	std::unordered_map<unsigned, std::vector<cell*>> cells_in_set;

	//	//initialize
	//	for (unsigned row = 0; row < grid->number_of_rows(); ++row)
	//	{
	//		for (unsigned collumn = 0; collumn < grid->number_of_collumns(); ++collumn)
	//		{
	//			unsigned set = (unsigned)set_for_cell.size();
	//			cell* current_cell = grid->get_cell(row, collumn);
	//			set_for_cell[current_cell] = set;
	//			cells_in_set[set].push_back(current_cell);

	//			if (current_cell->_neighbours[dir::SOUTH])
	//			{
	//				neighbours.push_back(std::make_pair(current_cell, current_cell->_neighbours[dir::SOUTH]));
	//			}
	//			if (current_cell->_neighbours[dir::EAST])
	//			{
	//				neighbours.push_back(std::make_pair(current_cell, current_cell->_neighbours[dir::EAST]));
	//			}
	//		}
	//	}

	//	//two small helper functions
	//	auto can_merge = [&](cell* left, cell* right) { return set_for_cell[left] != set_for_cell[right]; };

	//	auto merge = [&](cell* left, cell* right)
	//	{
	//		left->link_with(right);

	//		unsigned winner = set_for_cell[left];
	//		unsigned looser = set_for_cell[right];
	//		std::vector<cell*> loosers = cells_in_set[looser];
	//		if (loosers.size() == 0) { loosers.push_back(right); }

	//		for (auto cell : loosers)
	//		{
	//			cells_in_set[winner].push_back(cell);
	//			set_for_cell[cell] = winner;
	//		}

	//		cells_in_set.erase(looser);
	//	};

	//	//The generation algorithm here
	//	unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
	//	std::shuffle(neighbours.begin(), neighbours.end(), std::default_random_engine(seed));
	//	while (neighbours.size() > 0)
	//	{
	//		std::pair<cell*, cell*> pair = neighbours.back();
	//		neighbours.pop_back();
	//		if (can_merge(pair.first, pair.second))
	//		{
	//			merge(pair.first, pair.second);
	//		}
	//	}
	//}
	
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
	std::wstringstream grid::grid_to_utf8()
	{
		std::wstringstream ss;
		cell* current;
		cell temp(-1, -1);
		ss << L"┌";

		//first row
		for (unsigned i = 0; i < _collumns - 1; ++i)
		{
			ss << L"───";
			current = _grid[0][i];
			ss << (current->is_linked(current->east()) ? L"─" : L"┬");
		}
		ss << L"───" << L"┐";
		ss << "\n";

		for (unsigned row = 0; row < _rows; ++row)
		{
			std::wstring top = L"│"; //top part of square. starting wall to the left border edge

			current = _grid[row][0];
			std::wstring bottom;
			if (row == _rows - 1) //last bottom left corner
			{
				bottom = L"└";
			}
			else
			{
				bottom = (current->is_linked(current->south()) ? L"│" : L"├");
			}

			for (unsigned collumn = 0; collumn < _collumns; ++collumn)
			{
				current = get_cell(row, collumn);
				if (current == nullptr)
				{
					current = &temp;
				}
				cell* east = (current->east() ? current->east() : &temp);
				cell* south = (current->south() ? current->south() : &temp);
				cell* south_east = get_cell(current->_row + 1, current->_collumn + 1);

				std::wstring body = L"   ";
				std::wstring east_boundary = (current->is_linked(east) ? L" " : L"│");
				top += body + east_boundary;

				std::wstring south_boundary = (current->is_linked(south) ? L"   " : L"───");

				//potential corners: ┌ ┐ └ ┘ ├ ┤ ┬ ┴ ┼ *
				std::wstring corner;
				if (collumn == _collumns - 1)
				{
					if (row == _rows - 1)
					{
						corner = L"┘";
					}
					else
					{
						corner = (current->is_linked(south) ? L"│" : L"┤");
					}
				}
				else if (row == _rows - 1)
				{
					corner = (current->is_linked(east) ? L"─" : L"┴");
				}
				else
				{
					corner = helper::determine_corner_utf8(current, east, south, south_east);
				}

				bottom += south_boundary + corner;
			}
			ss << top << "\n" << bottom << "\n";
		}
		return ss;
	}

	std::wstring helper::determine_corner_utf8(cell* current, cell* east, cell* south, cell* south_east)
	{
		cell temp(-1, -1);
		if (south_east == nullptr)
		{
			south_east = &temp;
		}
		//potential corners: ┌ ┐ └ ┘ ├ ┤ ┬ ┴ ┼ * ─ │
		if (!current->is_linked(east))
			//wall between current and east
		{
			if (!current->is_linked(south))
				//wall between current and east
				//wall between current and south
			{
				if (!south->is_linked(south_east))
					//wall between current and east
					//wall between current and south
					//wall between south and south_east
				{
					if (!east->is_linked(south_east))
						//wall between current and east
						//wall between current and south
						//wall between south and south_east
						//wall between east and south_east
					{
						return L"┼"; //ok
					}
					else
						//wall between current and east
						//wall between current and south
						//wall between south and south_east
						//nothing between east and south_east
					{
						return L"┤"; //ok
					}
				}
				else
					//wall between current and east
					//wall between current and south
					//nothing between south and south_east
				{
					if (!east->is_linked(south_east))
						//wall between current and east
						//wall between current and south
						//nothing between south and south_east
						//wall between east and south_east
					{
						return L"┴"; //ok
					}
					else
						//wall between current and east
						//wall between current and south
						//nothing between south and south_east
						//nothing between east and south_east
					{
						return L"┘"; //ok
					}
				}
			}
			else
				//wall between current and east
				//nothing between current and south
			{
				if (!south->is_linked(south_east))
					//wall between current and east
					//nothing between current and south
					//wall between south and south_east
				{
					if (!east->is_linked(south_east))
						//wall between current and east
						//nothing between current and south
						//wall between south and south_east
						//wall between east and south_east
					{
						return L"├"; //ok
					}
					else
						//wall between current and east
						//nothing between current and south
						//wall between south and south_east
						//nothing between east and south_east
					{
						return L"│"; //ok
					}
				}
				else
					//wall between current and east
					//nothing between current and south
					//nothing between south and south_east
				{
					if (!east->is_linked(south_east))
						//wall between current and east
						//nothing between current and south
						//nothing between south and south_east
						//wall between east and south_east
					{
						return L"└"; //ok
					}
					else
						//wall between current and east
						//nothing between current and south
						//nothing between south and south_east
						//nothing between east and south_east
					{
						return L"╵"; //ok
					}
				}
			}
		}
		else
			//nothing between current and east
		{
			if (!current->is_linked(south))
				//nothing between current and east
				//wall between current and south
			{
				if (!south->is_linked(south_east))
					//nothing between current and east
					//wall between current and south
					//wall between south and south_east
				{
					if (!east->is_linked(south_east))
						//nothing between current and east
						//wall between current and south
						//wall between south and south_east
						//wall between east and south_east
					{
						return L"┬"; //ok
					}
					else
						//nothing between current and east
						//wall between current and south
						//wall between south and south_east
						//nothing between east and south_east
					{
						return L"┐"; //ok
					}
				}
				else
					//nothing between current and east
					//wall between current and south
					//nothing between south and south_east
				{
					if (!east->is_linked(south_east))
						//nothing between current and east
						//wall between current and south
						//nothing between south and south_east
						//wall between east and south_east
					{
						return L"─"; //ok
					}
					else
						//nothing between current and east
						//wall between current and south
						//nothing between south and south_east
						//nothing between east and south_east
					{
						return L"╴"; //ok
					}
				}
			}
			else
				//nothing between current and east
				//nothing between current and south
			{
				if (!south->is_linked(south_east))
					//nothing between current and east
					//nothing between current and south
					//wall between south and south_east
				{
					if (!east->is_linked(south_east))
						//nothing between current and east
						//nothing between current and south
						//wall between south and south_east
						//wall between east and south_east
					{
						return L"┌"; //ok
					}
					else
						//nothing between current and east
						//nothing between current and south
						//wall between south and south_east
						//nothing between east and south_east
					{
						return L"╷"; //ok
					}
				}
				else
					//nothing between current and east
					//nothing between current and south
					//nothing between south and south_east
				{
					if (!east->is_linked(south_east))
						//nothing between current and east
						//nothing between current and south
						//nothing between south and south_east
						//wall between east and south_east
					{
						return L"╶"; //ok
					}
					else
						//nothing between current and east
						//nothing between current and south
						//nothing between south and south_east
						//nothing between east and south_east
					{
						return L"*";
					}
				}
			}
		}
	}
}