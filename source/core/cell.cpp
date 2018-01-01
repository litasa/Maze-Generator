#include "cell.h"
#include <algorithm>

namespace maze
{
    void cell::link_with(cell* cell, bool bidirectional)
    {
        if (cell != nullptr)
        {
            _links.push_back(cell);
            if (bidirectional)
            {
                cell->link_with(this, false);
            }
        }
    }

    void cell::link_with(dir dir, bool bidirectional)
    {
        link_with(_neighbours[dir], bidirectional);
    }

    void cell::unlink(cell* target, bool bidirectional)
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

    void cell::unlink(dir dir, bool bidirectional)
    {
        this->unlink(_neighbours[dir], bidirectional);
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