#include "problem_10.hpp"

namespace aoc2022
{
	bool op::cycle()
	{
		m_remaining_cycles--;
		if (m_remaining_cycles < 0)
		{
			complete();
			return true;
		}

		return false;
	}

	void add_op::complete()
	{
		m_cpu->m_rx += m_amount;
	}
}
