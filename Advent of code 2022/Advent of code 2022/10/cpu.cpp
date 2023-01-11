
#include "cpu.hpp"

#include "op.hpp"

#include <iostream>

namespace aoc2022
{
	void cpu::execute(const std::vector<std::string>& args)
	{
		if (has_op())
		{
			throw std::exception("cant execute command, cpu is busy");
		}

		op* op;
		if (args[0] == "noop")
		{
			op = new noop{ this };
		}
		else
		{
			const int amount = atoi(args[1].c_str());
			op = new add_op{ amount, this };
		}
		m_op = op;
	}

	void cpu::cycle() const
	{
		if (m_op)
		{
			m_op->cycle();
		}
	}

	void cpu::finish_cycle()
	{
		if (m_op)
		{
			if (m_op->done())
			{
				m_op->complete();

				//delete m_op;
				m_op = nullptr;
			}
		}
	}
}