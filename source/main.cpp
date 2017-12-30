#include <iostream>

#include "maze_generation.h"

void problem(unsigned line)
{
	std::wcout << "Problem at : " << line << std::endl;
}
int main()
{
	int width, height;
	width = height = 15;
	maze::grid g(width, height);
	/*************
	Testing to get cell outside of grid
	**************/
		//outside to left
		if (g.get_cell(-1, 0) != nullptr) { problem(__LINE__); }
		//outside to right
		if (g.get_cell(width + 1, 0) != nullptr) { problem(__LINE__); }
		//outside above
		if (g.get_cell(0, -1) != nullptr) { problem(__LINE__); }
		//outside below
		if (g.get_cell(0, height + 1) != nullptr) { problem(__LINE__); }
	g.print_to_console();
	apply_kruskal(&g);
	g.print_to_console();
	g.save_as_txt("test.txt");

	std::cin.get();
}