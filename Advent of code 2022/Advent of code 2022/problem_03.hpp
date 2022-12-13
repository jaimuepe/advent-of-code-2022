#pragma once

#include "problem.hpp"

namespace aoc2022
{
	constexpr int DAY = 3;

	class problem_03 : public problem
	{
	public:
		problem_03() : problem(3) {}

		A_IMPL()
		{
			int sum = 0;

			for (auto& line : lines)
			{
				auto& rucksack = line;

				size_t rucksack_size = rucksack.length();
				size_t compartment_size = rucksack_size / 2;

				for (size_t i = 0; i < compartment_size; i++)
				{
					bool found = false;

					char a = rucksack[i];

					for (size_t j = compartment_size; j < rucksack_size; j++)
					{
						char b = rucksack[j];

						if (a == b)
						{
							found = true;
							sum += to_priority(a);
							break;
						}
					}

					if (found) break;
				}
			}

			print_result(sum);
		}

		B_IMPL()
		{
			int sum = 0;

			for (size_t i = 0; i < lines.size(); i += 3)
			{
				auto& rucksack0 = lines[i];
				auto& rucksack1 = lines[i + 1];
				auto& rucksack2 = lines[i + 2];

				char badge = '\0';

				for (char& c : rucksack0)
				{
					if (rucksack1.find(c) != -1 && rucksack2.find(c) != -1)
					{
						badge = c;
						break;
					}
				}

				sum += to_priority(badge);
			}

			print_result(sum);
		}

	private:

		int to_priority(char c)
		{
			if (c > 'Z') return c - 'a' + 1;
			return c - 'A' + 27;
		}
	};
}