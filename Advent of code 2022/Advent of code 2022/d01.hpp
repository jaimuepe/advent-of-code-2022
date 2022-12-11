#pragma once

#include "common.hpp"

namespace d01
{
	namespace b
	{
		constexpr size_t N = 3;

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

		void run()
		{
			auto lines = get_lines();

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

				sum += atoi(line);
			}

			if (sum > 0)
			{
				update_if_highest(top_elves, sum);
			}

			int total_sum = 0;

			for (int i = 0; i < N; i++)
			{
				std::cout << "elf #" << i << ": " << top_elves[i] << '\n';
				total_sum += top_elves[i];
			}

			std::cout << total_sum << '\n';
		}
	}
}