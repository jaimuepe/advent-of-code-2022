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

	void cpu::execute(op* op)
	{
		m_ops.push_back(op);
	}

	void cpu::cycle()
	{
		m_cycles++;

		for (int i = static_cast<int>(m_ops.size()) - 1; i >= 0; i--)
		{
			auto& op = m_ops[i];
			if (op->cycle())
			{
				delete m_ops[i];
				m_ops.erase(m_ops.begin() + i);
			}
		}
	}
}
