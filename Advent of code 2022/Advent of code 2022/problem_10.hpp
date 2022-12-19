#pragma once

#include "problem.hpp"

#include "cpu.hpp"
#include "crt.hpp"

namespace aoc2022
{
	class problem_10 : public problem
	{
	public:
		problem_10() : problem(10) {}

		A_IMPL()
		{
			cpu cpu{};

			int total_signal_strength = 0;

			int i = 0;

			while (i < lines.size())
			{
				cpu.start_cycle();

				if (!cpu.has_op())
				{
					auto& line = lines[i++];

					std::vector args = split(line, ' ');
					cpu.execute(args);
				}

				cpu.cycle();

				int cycles = cpu.cycles();
				if (cycles == 20 || cycles > 40 && ((cycles - 20) % 40) == 0)
				{
					total_signal_strength += cpu.cycles() * cpu.rx();
				}

				cpu.finish_cycle();
			}

			print_result(total_signal_strength);
		}

		B_IMPL()
		{
			cpu cpu{};

			crt crt{ &cpu };

			int i = 0;

			while (i < lines.size())
			{
				cpu.start_cycle();

				if (!cpu.has_op())
				{
					auto& line = lines[i++];

					std::vector args = split(line, ' ');
					cpu.execute(args);
				}

				cpu.cycle();
				crt.update();

				cpu.finish_cycle();
			}

			crt.draw();
		}
	};
}

