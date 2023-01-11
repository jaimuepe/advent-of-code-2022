#pragma once

#include "problem.hpp"

#include "10/cpu.hpp"
#include "10/crt.hpp"

namespace aoc2022
{
    class problem_10 final : public problem
    {
    public:
        problem_10() : problem(10)
        {
        }

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

                const int cycles = cpu.cycles();
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

            crt crt{&cpu};

            size_t i = 0;

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
