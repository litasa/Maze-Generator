#include "cell.h"
#include <algorithm>

namespace maze
{
    bool cell::link_with(cell* cell, bool bidirectional)
    {
        if (cell != nullptr)
        {
            if (bidirectional)
            {
                cell->link_with(this, false);
            }
            _links.push_back(cell);
            return true;
        }
        return false;
    }

    bool cell::link_with(dir dir, bool bidirectional)
    {
        return link_with(_neighbours[dir], bidirectional);
    }

    bool cell::unlink(cell* target, bool bidirectional)
    {
        std::size_t size_before = _links.size();
        if (target != nullptr)
        {
            if (bidirectional)
            {
                auto in_links = std::find(_links.begin(), _links.end(), target);
                if (in_links != _links.end())
                {
                    bool success = (*in_links)->unlink(this, false);
                    if (!success)
                    {
                        return false;
                    }
                }
            }
            _links.erase(std::remove_if(_links.begin(), _links.end(), [&target](maze::cell* i) {return i == target; }), _links.end());
            return size_before > _links.size();
        }
        return false;
    }

    bool cell::unlink(dir dir, bool bidirectional)
    {
        return this->unlink(_neighbours[dir], bidirectional);
    }

    bool cell::is_linked(cell* cell)
    {
        return std::find(_links.begin(), _links.end(), cell) != _links.end();
    }

    bool cell::is_linked_with_neighbour(dir dir)
    {
        return has_neighbour(dir) && is_linked(_neighbours[dir]);
    }

    bool cell::has_neighbour(dir dir)
    {
        return _neighbours[dir] != nullptr;
    }

    cell* cell::get_neighbour(dir dir)
    {
        return _neighbours[dir];
    }
}

maze::dir maze::helper::opposite_dir(maze::dir dir)
{
    switch (dir)
    {
    case maze::NORTH:
        return maze::SOUTH;
    case maze::SOUTH:
        return maze::NORTH;
    case maze::WEST:
        return maze::EAST;
    case maze::EAST:
        return maze::WEST;
    default:
        return maze::NORTH;
    }
}

void maze::helper::set_neighbours(cell * current, dir dir, cell * neighbour)
{
    current->_neighbours[dir] = neighbour;
    neighbour->_neighbours[opposite_dir(dir)] = current;
}
