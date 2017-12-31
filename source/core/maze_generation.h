#pragma once

#include <vector>
#include <algorithm>

#include <unordered_map>

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

        void unlink(cell* target, bool bidirectional = true)
        {
            if (target != nullptr)
            {
                if (bidirectional)
                {
                    cell* linkee = *std::find(_links.begin(), _links.end(), target);
                    linkee->unlink(this, false);
                }
                _links.erase(std::remove_if(_links.begin(), _links.end(), [&target](maze::cell* i) {return i == target; }), _links.end());
            }
        }

        void unlink(dir dir, bool bidirectional = true)
        {
            this->unlink(_neighbours[dir], bidirectional);
        }

        bool is_linked(cell* cell)
        {
            return std::find(_links.begin(), _links.end(), cell) != _links.end();
        }

        bool is_linked_with_neighbour(dir dir)
        {
            return has_neighbour(dir) && is_linked(_neighbours[dir]);
        }

        bool has_neighbour(dir dir)
        {
            return _neighbours[dir] != nullptr;
        }

        cell* get_neighbour(dir dir)
        {
            return _neighbours[dir];
        }

        cell* east() { return _neighbours[dir::EAST]; }
        cell* west() { return _neighbours[dir::WEST]; }
        cell* north() { return _neighbours[dir::NORTH]; }
        cell* south() { return _neighbours[dir::SOUTH]; }

    };

    // The origin is the top left corner.
    // Iterating over rows equals going east
    // Iterating over collumns equals going south
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

}