#pragma once

#include "cpu.hpp"
#include "../grid.hpp"

#include <iostream>

namespace aoc2022
{
	constexpr size_t CRT_HEIGHT = 6;
	constexpr size_t CRT_WIDTH = 40;

	struct cpu;

	struct crt
	{
		explicit crt(cpu* cpu);

		void update();
		
		void draw();

	private:
		cpu* m_cpu;

		grid<char> m_grid;
	};
}

