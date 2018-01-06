#include "io.h"

#include <iostream>
#include <fstream>

#include <io.h>    // for _setmode()
#include <fcntl.h> // for _O_U16TEXT

#include "../core/grid.h"
#include "../core/cell.h"
namespace maze
{
    namespace io
    {
        void print_to_console(grid* grid)
        {
            //potential corners: ┌ ┐ └ ┘ ├ ┤ ┬ ┴ ┼ *

            //assumption. All outer edges are closed
            int prev_mode = _setmode(_fileno(stdout), _O_U16TEXT);
            std::wstringstream ss = grid_to_utf8(grid);
            std::wcout << ss.str();
            _setmode(_fileno(stdout), prev_mode);
        }

        void save_as_txt(grid* grid, const char* path)
        {
            std::wstringstream ss = grid_to_utf8(grid);
            FILE *file;
            fopen_s(&file, "test.txt", "w,ccs=UTF-8");
            fwprintf(file, ss.str().c_str());
            fclose(file);
        }

        std::wstringstream grid_to_utf8(grid* grid)
        {
            std::wstringstream ss;
            cell* current;
            cell temp(-1, -1);
            ss << L"┌";

            //first row
            for (unsigned collumn = 0; collumn < grid->number_of_collumns() - 1; ++collumn)
            {
                ss << L"───";
                current = grid->get_cell(0,collumn);
                ss << (current->is_linked(current->east()) ? L"─" : L"┬");
            }
            ss << L"───" << L"┐";
            ss << "\n";

            for (unsigned row = 0; row < grid->number_of_rows(); ++row)
            {
                std::wstring top = L"│"; //top part of square. starting wall to the left border edge

                current = grid->get_cell(row, 0);
                std::wstring bottom;
                if (row == grid->number_of_collumns() - 1) //last bottom left corner
                {
                    bottom = L"└";
                }
                else
                {
                    bottom = (current->is_linked(current->south()) ? L"│" : L"├");
                }

                for (unsigned collumn = 0; collumn < grid->number_of_collumns(); ++collumn)
                {
                    current = grid->get_cell(row, collumn);
                    if (current == nullptr)
                    {
                        current = &temp;
                    }
                    cell* east = (current->east() ? current->east() : &temp);
                    cell* south = (current->south() ? current->south() : &temp);
                    cell* south_east = grid->get_cell(current->_row + 1, current->_collumn + 1);

                    std::wstring body = L"   ";
                    std::wstring east_boundary = (current->is_linked(east) ? L" " : L"│");
                    top += body + east_boundary;

                    std::wstring south_boundary = (current->is_linked(south) ? L"   " : L"───");

                    //potential corners: ┌ ┐ └ ┘ ├ ┤ ┬ ┴ ┼ *
                    std::wstring corner;
                    if (collumn == grid->number_of_collumns() - 1)
                    {
                        if (row == grid->number_of_rows() - 1)
                        {
                            corner = L"┘";
                        }
                        else
                        {
                            corner = (current->is_linked(south) ? L"│" : L"┤");
                        }
                    }
                    else if (row == grid->number_of_rows() - 1)
                    {
                        corner = (current->is_linked(east) ? L"─" : L"┴");
                    }
                    else
                    {
                        corner = determine_corner_utf8(current, east, south, south_east);
                    }

                    bottom += south_boundary + corner;
                }
                ss << top << "\n" << bottom << "\n";
            }
            return ss;
        }

        std::wstring determine_corner_utf8(cell* current, cell* east, cell* south, cell* south_east)
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

        std::string toString(cell * cell)
        {
            std::stringstream ss;
            if (cell)
                ss << "(" << cell->x() << ", " << cell->y() << ")";
            else
                ss << "(null)";
            return ss.str();
        }

        void print_shortest_path(std::vector<cell*>& vec)
        {
            for (unsigned i = 0; i < vec.size(); ++i)
            {
                cell* cell = vec[i];
                std::cout << toString(cell);
                if (i != vec.size() - 1)
                {
                     std::cout << "->";
                }
            }
            std::cout << std::endl;
        }
    }
}

