#pragma once

#include <vector>
#include <algorithm>

#include <unordered_map>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

#include <io.h>    // for _setmode()
#include <fcntl.h> // for _O_U16TEXT

namespace maze {


	enum dir
	{
		NORTH,
		SOUTH,
		WEST,
		EAST,
	};
	struct cell
	{
		uint32_t _row, _collumn;
		cell* _neighbours[4];
		std::vector<cell*> _links;

		cell(uint32_t row, uint32_t collumn) : _row(row), _collumn(collumn) { };

		void link_with(cell* cell, bool bidirectional = true)
		{
			_links.push_back(cell);
			if (bidirectional)
			{
				cell->link_with(this, false);
			}
		}

		void unlink(cell* cell, bool bidirectional = true)
		{
			_links.erase(std::remove_if(_links.begin(), _links.end(), [&cell](maze::cell* i) {return i == cell; }), _links.end());
		}

		bool is_linked(cell* cell)
		{
			return std::find(_links.begin(), _links.end(), cell) != _links.end();
		}

		bool is_linked_with_neighbour(dir dir)
		{
			return got_neighbour(dir) && is_linked(_neighbours[dir]);
		}

		bool got_neighbour(dir dir)
		{
			return _neighbours[dir] != nullptr;
		}

		cell* east() { return _neighbours[dir::EAST]; }
		cell* west() { return _neighbours[dir::WEST]; }
		cell* north() { return _neighbours[dir::NORTH]; }
		cell* south() { return _neighbours[dir::SOUTH]; }

	};

	namespace helper
	{
		std::wstring determine_corner_utf8(cell* current, cell* east, cell* south, cell* south_east);
	}

	struct grid
	{
		grid(uint32_t rows, uint32_t collumns);

		~grid();

		cell* get_cell(int row, int collumn);
		void save_as_txt(const char* path);
		void print_to_console();

		uint32_t number_of_cells() { return _rows*_collumns; }
		uint32_t number_of_rows() { return _rows; }
		uint32_t number_of_collumns() { return _collumns; }

	private:
		void initialize();
		void setup_cells();
		std::wstringstream grid_to_utf8();

		uint32_t _rows, _collumns;
		std::vector<std::vector<cell*>> _grid;
	};

	void apply_kruskal(grid* grid);


}