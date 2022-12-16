#pragma once

#include "problem.hpp"
#include <deque>

namespace aoc2022
{
	struct crate_stack
	{
		std::deque<char> stack;
	};

	struct crate_movement
	{
		int from;
		int to;
		int amount;
	};

	class problem_05 : public problem
	{
	public:
		problem_05() : problem(5) {}

		A_IMPL()
		{
			int next_index;

			auto crate_stacks = get_crate_stacks(lines, next_index);

			auto movements = get_crate_movements(lines, next_index);

			for (auto& movement : movements)
			{
				auto& from = crate_stacks[movement.from];
				auto& to = crate_stacks[movement.to];

				for (int i = 0; i < movement.amount; i++)
				{
					char c = from.stack.back();
					from.stack.pop_back();

					to.stack.push_back(c);
				}
			}

			print_stack_topmost_crate(crate_stacks);
		}

		B_IMPL()
		{
			int next_index;

			auto crate_stacks = get_crate_stacks(lines, next_index);

			auto movements = get_crate_movements(lines, next_index);

			for (auto& movement : movements)
			{
				auto& from = crate_stacks[movement.from];
				auto& to = crate_stacks[movement.to];

				int x = movement.amount;

				for (int i = x - 1; i >= 0; i--)
				{
					char c = from.stack[from.stack.size() - 1 - i];
					to.stack.push_back(c);
				}

				for (int i = 0; i < x; i++)
				{
					from.stack.pop_back();
				}
			}

			print_stack_topmost_crate(crate_stacks);
		}

	private:

		void print_stack_topmost_crate(std::vector<crate_stack>& crate_stacks)
		{
			for (auto& stack : crate_stacks)
			{
				std::cout << stack.stack.back();
			}
			std::cout << '\n';
		}

		std::vector<crate_stack> get_crate_stacks(std::vector<std::string>& lines, int& index)
		{
			std::vector<crate_stack> crate_stacks{};

			index = 0;
			while (index < lines.size())
			{
				auto& line = lines[index++];

				int crate_index = 0;

				bool exit = false;

				while (true)
				{
					int j = 1 + 4 * crate_index;

					if (j >= line.size()) break;

					char c = line[j];

					if (std::isdigit(c))
					{
						exit = true;
						break;
					}

					if (!std::isspace(c))
					{
						while (crate_index >= crate_stacks.size())
						{
							crate_stacks.push_back(crate_stack{});
						}

						auto& crate_stack = crate_stacks[crate_index];
						crate_stack.stack.push_front(c);
					}

					crate_index++;
				}

				if (exit)
				{
					break;
				}
			}

			// add one for the empty line
			index++;

			return crate_stacks;
		}

		std::vector<crate_movement> get_crate_movements(std::vector<std::string>& lines, int start_index)
		{
			std::vector<crate_movement> movements{};

			for (int i = start_index; i < lines.size(); i++)
			{
				auto& line = lines[i];

				int amount, from, to;
				sscanf_s(line.c_str(), "move %i from %i to %i", &amount, &from, &to);

				crate_movement movement{};
				movement.amount = amount;
				movement.from = from - 1;
				movement.to = to - 1;

				movements.push_back(movement);
			}

			return movements;
		}
	};
}

