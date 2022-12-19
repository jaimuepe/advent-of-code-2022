#pragma once

#include "grid.hpp"

#include <string>
#include <vector>

namespace aoc2022
{
	struct op;

	struct cpu
	{
		friend struct add_op;

		void execute(std::vector<std::string>& args);

		inline void start_cycle() { m_cycles++; }

		void cycle();

		void finish_cycle();

		inline int cycles() { return m_cycles; }

		inline int rx() { return m_rx; }

		inline bool has_op() { return m_op != nullptr; }

	private:

		int m_cycles{ 0 };

		int m_rx{ 1 };

		op* m_op{};
	};
}

