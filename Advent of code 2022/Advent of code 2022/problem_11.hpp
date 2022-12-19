#pragma once

#include "monkey.hpp"
#include "problem.hpp"

#include <functional>

namespace aoc2022
{

	class problem_11 : public problem
	{
	public:
		problem_11() : problem(11) {}

		A_IMPL()
		{
			for (size_t i = 0; i < lines.size(); i += 7)
			{
				auto& monkey = lines[i];
				auto& starting_items = lines[i + 1];
				auto& operation = lines[i + 2];
				auto& test = lines[i + 3];
				auto& if_true = lines[i + 4];
				auto& if_false = lines[i + 5];

				parse_monkey(
					monkey,
					starting_items,
					operation,
					test,
					if_true,
					if_false);
			}
		}

		B_IMPL()
		{
		}

	private:

		void parse_monkey(
			std::string& monkey,
			std::string& starting_items,
			std::string& operation,
			std::string& test,
			std::string& if_true,
			std::string& if_false)
		{
			int index;
			sscanf_s(monkey.c_str(), "Monkey %i:", &index);

			auto op = [&operation](int old)
			{
				constexpr std::string_view prefix{ "  Operation: new = " };

				std::string substr = operation.substr(prefix.size());
				auto tokens = split(substr, ' ');

				int a;
				if (tokens[0] == "old")
				{
					a = old;
				}
				else
				{
					a = atoi(tokens[0].c_str());
				}

				int b;
				if (tokens[2] == "old")
				{
					b = old;
				}
				else
				{
					b = atoi(tokens[2].c_str());
				}

				if (tokens[1] == "+")
				{
					return a + b;
				}
				else if (tokens[1] == "*")
				{
					return a * b;
				}
				else
				{
					std::cerr << "invalid op symbol: " << tokens[1] << '\n';
					return 0;
				}
			};

			auto op = [](int worry_level)
			{
				return false;
			};

			return;
		}
	};
}

