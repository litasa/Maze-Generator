
#include <vector>
#include <algorithm>

#include <unordered_map>

//Forward decleration
namespace maze
{
    struct cell;
}

    // The origin is the top left corner.
    // Iterating over rows equals going east
    // Iterating over collumns equals going south
namespace maze
{
    class grid
    {
    public:
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
