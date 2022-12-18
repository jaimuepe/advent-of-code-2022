#pragma once

#include "problem.hpp"

namespace aoc2022
{
	constexpr int NOOP_CYCLES = 1;
	constexpr int ADDX_CYCLES = 2;

	struct cpu;

	struct op
	{
		inline op(cpu* cpu, int remaining_cycles) :
			m_cpu{ cpu },
			m_remaining_cycles{ remaining_cycles }
		{}

		bool cycle();

	protected:
		cpu* m_cpu;

	private:

		int m_remaining_cycles;
		virtual void complete() = 0;
	};

	struct add_op : public op
	{
		inline add_op(int amount, cpu* cpu) :
			m_amount{ amount },
			op{ cpu, ADDX_CYCLES }
		{}

	protected:
		void complete() override;

	private:
		int m_amount;
	};

	struct cpu
	{
		friend struct add_op;

		void execute(op* op);
		void cycle();

		inline int cycles() { return m_cycles; }

		inline int rx() { return m_rx; }

	private:
		int m_cycles{ 0 };
		int m_rx{ 1 };
		std::vector<op*> m_ops{};
	};

	class problem_10 : public problem
	{
	public:
		problem_10() : problem(10) {}

		A_IMPL()
		{
			cpu cpu{};

			int total_signal_strength = 0;

			for (auto& line : lines)
			{
				std::vector tokens = split(line, ' ');

				cpu.cycle();

				if (tokens[0] == "noop")
				{
					// nothing
				}
				else
				{
					int amount = atoi(tokens[1].c_str());

					add_op* op = new add_op{ amount, &cpu };
					cpu.execute(op);
				}

				if (cpu.cycles() % 20 == 0)
				{
					total_signal_strength += cpu.cycles() * cpu.rx();
				}

				std::cout << "cycle: " << cpu.cycles() << ", rx = " << cpu.rx() << '\n';
			}

			print_result(total_signal_strength);
		}

		B_IMPL()
		{
		}
	};
}

