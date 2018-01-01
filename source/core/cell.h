#pragma once
#include <vector>

namespace maze
{
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

        void link_with(cell* cell, bool bidirectional = true);

        void link_with(dir dir, bool bidirectional = true);

        void unlink(cell* target, bool bidirectional = true);

        void unlink(dir dir, bool bidirectional = true);

        bool is_linked(cell* cell);

        bool is_linked_with_neighbour(dir dir);

        bool has_neighbour(dir dir);

        cell* get_neighbour(dir dir);

        cell* east() { return _neighbours[dir::EAST]; }
        cell* west() { return _neighbours[dir::WEST]; }
        cell* north() { return _neighbours[dir::NORTH]; }
        cell* south() { return _neighbours[dir::SOUTH]; }

    };
}
 