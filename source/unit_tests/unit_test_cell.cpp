#include "../core/cell.h"
#include "../../dependencies/catch.hpp"

bool is_cell_empty(maze::cell* cell)
{
    bool empty = true;
    for (auto neighbour : cell->_neighbours)
    {
        if (neighbour != nullptr)
        {
            return false;
        }
    }
    return cell->_links.empty();
}
// Setup data works
TEST_CASE( "Cell x and y corresponds to collumn and row", "[single-file]" ) {
    maze::cell* cell = new maze::cell(0, 0);
    REQUIRE(cell->x() == cell->_collumn);
    REQUIRE(cell->y() == cell->_row);
    REQUIRE(cell->_collumn == 0);
    REQUIRE(cell->_row == 0);
    delete cell;
}

TEST_CASE( "Linking and unlinking 2 cells", "[single-file]" ) {
    maze::cell* cell_first = new maze::cell(0, 0);
    maze::cell* cell_second = new maze::cell(1, 1);

    SECTION("Bidirectional linking")
    {
        //bidirectional link
        REQUIRE(cell_first->link_with(cell_second));

        REQUIRE(cell_first->is_linked(cell_second));
        REQUIRE(cell_first->_links.size());
        REQUIRE(cell_second->is_linked(cell_first));

        REQUIRE_FALSE(is_cell_empty(cell_first));
        REQUIRE_FALSE(is_cell_empty(cell_second));
    }
    
    SECTION("Bidirectional unlinking")
    {
        //do a bidirectional link first
        cell_first->link_with(cell_second);

        REQUIRE(cell_second->unlink(cell_first));

        REQUIRE_FALSE(cell_first->is_linked(cell_second));
        REQUIRE_FALSE(cell_second->is_linked(cell_first));

        REQUIRE(is_cell_empty(cell_first));
        REQUIRE(is_cell_empty(cell_second));
    }

    SECTION("Single linking")
    {
        REQUIRE(cell_first->link_with(cell_second, false));

        REQUIRE(cell_first->is_linked(cell_second));
        REQUIRE_FALSE(cell_second->is_linked(cell_first));

        REQUIRE_FALSE(is_cell_empty(cell_first));
        REQUIRE(is_cell_empty(cell_second));
    }

    THEN("Single unlinkning")
    {
        //do a bidirectional link first
        cell_first->link_with(cell_second);

        REQUIRE(cell_first->unlink(cell_second, false));

        REQUIRE_FALSE(cell_first->is_linked(cell_second));
        REQUIRE(cell_second->is_linked(cell_first));

        REQUIRE(is_cell_empty(cell_first));
        REQUIRE_FALSE(is_cell_empty(cell_second));
    }

    delete cell_first;
    delete cell_second;
}

SCENARIO("Setting neighbours 2 cells", "[single-file]")
{
    GIVEN("Two cells")
    {
        maze::cell* cell_first = new maze::cell(0, 0);
        maze::cell* cell_second = new maze::cell(0, 1);

        REQUIRE_FALSE(cell_first->has_neighbour(maze::EAST));
        REQUIRE_FALSE(cell_first->has_neighbour(maze::SOUTH));
        REQUIRE_FALSE(cell_first->has_neighbour(maze::WEST));
        REQUIRE_FALSE(cell_first->has_neighbour(maze::NORTH));

        WHEN("Setting them as NORTH / SOUTH neighbours")
        {
            maze::helper::set_neighbours(cell_first, maze::NORTH, cell_second);

            THEN("cell->has_neighbour should return true only if there is a neighbour")
            {
                // cell_first has a neighbour north
                REQUIRE(cell_first->has_neighbour(maze::NORTH));
                REQUIRE_FALSE(cell_first->has_neighbour(maze::SOUTH));
                REQUIRE_FALSE(cell_first->has_neighbour(maze::EAST));
                REQUIRE_FALSE(cell_first->has_neighbour(maze::WEST));

                // cell_second has a neighbour south
                REQUIRE(cell_second->has_neighbour(maze::SOUTH));
                REQUIRE_FALSE(cell_second->has_neighbour(maze::NORTH));
                REQUIRE_FALSE(cell_second->has_neighbour(maze::EAST));
                REQUIRE_FALSE(cell_second->has_neighbour(maze::WEST));
            }

            THEN("cell->get_neighbour should return the other cell only if there is a neighbour")
            {
                REQUIRE(cell_first->get_neighbour(maze::NORTH) == cell_second);
                REQUIRE(cell_first->get_neighbour(maze::SOUTH) == nullptr);
                REQUIRE(cell_first->get_neighbour(maze::EAST)  == nullptr);
                REQUIRE(cell_first->get_neighbour(maze::WEST)  == nullptr);

                REQUIRE(cell_second->get_neighbour(maze::SOUTH) == cell_first);
                REQUIRE(cell_second->get_neighbour(maze::NORTH) == nullptr);
                REQUIRE(cell_second->get_neighbour(maze::EAST)  == nullptr);
                REQUIRE(cell_second->get_neighbour(maze::WEST)  == nullptr);
            }
        }
        // Cleanup
        delete cell_first;
        delete cell_second;
    } // Given: Two cells
} // Testcase: Setting neighbours 2 cells

TEST_CASE("Linking and unlinking multiple cells", "[single-file]")
{
    maze::cell* cell_first = new maze::cell(0, 0);
    maze::cell* cell_second = new maze::cell(1, 1);
    maze::cell* cell_third = new maze::cell(0, 1);
    maze::cell* cell_fourth = new maze::cell(1, 0);
    // 1  =  2
    // ||   ||
    // 3  =  4

    //Setting up links
    REQUIRE(cell_first->link_with(cell_second));
    REQUIRE(cell_first->link_with(cell_third));
    REQUIRE(cell_fourth->link_with(cell_third));
    REQUIRE(cell_fourth->link_with(cell_second));

    //Setting up neighbours
    maze::helper::set_neighbours(cell_first, maze::EAST, cell_second);

    SECTION("Testing nonexisting links")
    {
        REQUIRE_FALSE(cell_first->is_linked(cell_fourth));
        REQUIRE_FALSE(cell_fourth->is_linked(cell_first));
    }

    delete cell_first;
    delete cell_second;
    delete cell_third;
    delete cell_fourth;
}