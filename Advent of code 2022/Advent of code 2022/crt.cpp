#include "crt.hpp"

namespace aoc2022
{
	crt::crt(cpu* cpu) : m_cpu{ cpu }, m_grid{ CRT_HEIGHT , CRT_WIDTH, '.' } {}

	void crt::update()
	{
		int cycle_idx = m_cpu->cycles() - 1;

		int pixel_col = cycle_idx % 40;
		int pixel_row = cycle_idx / 40;

		int sprite_col = m_cpu->rx();

		for (int i = sprite_col - 1; i <= sprite_col + 1; i++)
		{
			if (pixel_col == i)
			{
				m_grid.set('#', pixel_row, i);
				break;
			}
		}
	}

	void crt::draw()
	{
		std::cout << "cycle " << m_cpu->cycles() << "\n\n";
		m_grid.print();
		std::cout << '\n';
	}
}