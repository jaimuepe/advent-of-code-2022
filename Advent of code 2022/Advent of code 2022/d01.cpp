#include <array>

#include "d01.hpp"
#include "common.hpp"

constexpr size_t n = 3;

void update_if_highest(std::array<int, n>& highest_values, int val)
{
	for (size_t i = 0; i < n; i++)
	{
		if (val > highest_values[i])
		{
			// shift and update
			for (size_t j = n - 1; j > i; j--)
			{
				highest_values[j] = highest_values[j - 1];
			}
			highest_values[i] = val;

			break;
		}
	}
}

void run_01()
{
	auto lines = get_lines();

	int sum = 0;

	std::array<int, 3> top_three_elves{};

	for (auto& line : lines)
	{
		if (line.empty())
		{
			update_if_highest(top_three_elves, sum);
			sum = 0;
			continue;
		}

		sum += atoi(line);
	}

	if (sum > 0)
	{
		update_if_highest(top_three_elves, sum);
	}

	int total_sum = 0;

	for (int i = 0; i < n; i++)
	{
		std::cout << "elf #" << i << ": " << top_three_elves[i] << '\n';
		total_sum += top_three_elves[i];
	}

	std::cout << total_sum << '\n';
}