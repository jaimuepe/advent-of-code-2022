#pragma once

namespace aoc2022
{
	struct cpu;

	constexpr int NOOP_CYCLES = 1;
	constexpr int ADDX_CYCLES = 2;

	struct op
	{
		inline op(cpu* cpu, int remaining_cycles) :
			m_cpu{ cpu }, m_remaining_cycles{ remaining_cycles } {}

		inline void cycle()
		{
			if (done())
			{
				throw std::exception("cannot cycle op, its already done");
			}
			m_remaining_cycles--;
		}

		inline bool done() { return m_remaining_cycles == 0; }

		virtual void complete() = 0;

	protected:
		cpu* m_cpu;

	private:

		int m_remaining_cycles;
	};

	struct add_op : public op
	{
		inline add_op(int amount, cpu* cpu) :
			m_amount{ amount }, op{ cpu, ADDX_CYCLES } {}

	protected:
		inline void complete() override { m_cpu->m_rx += m_amount; }

	private:
		int m_amount;
	};

	struct noop : public op
	{
		inline noop(cpu* cpu) : op{ cpu , NOOP_CYCLES } {}

	protected:
		void complete() override {}
	};
}