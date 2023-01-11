#pragma once

#include "problem.hpp"

#include <array>

namespace aoc2022
{
    constexpr size_t N = 3;

    class problem_01 final : public problem
    {
    public:
        problem_01() : problem(1)
        {
        }

    protected:
        virtual void run_a_impl(std::vector<std::string>&) override
        {
        }

        virtual void run_b_impl(std::vector<std::string>& lines) override
        {
            int sum = 0;

            std::array<int, N> top_elves{};

            for (auto& line : lines)
            {
                if (line.empty())
                {
                    update_if_highest(top_elves, sum);
                    sum = 0;
                    continue;
                }

                sum += atoi(line.c_str());
            }

            if (sum > 0)
            {
                update_if_highest(top_elves, sum);
            }

            int total_sum = 0;

            for (int i = 0; i < N; i++)
            {
                total_sum += top_elves[i];
            }

            print_result(total_sum);
        }

    private:
        void update_if_highest(std::array<int, N>& highest_values, int val)
        {
            for (size_t i = 0; i < N; i++)
            {
                if (val > highest_values[i])
                {
                    // shift and update
                    for (size_t j = N - 1; j > i; j--)
                    {
                        highest_values[j] = highest_values[j - 1];
                    }
                    highest_values[i] = val;

                    break;
                }
            }
        }
    };
}
