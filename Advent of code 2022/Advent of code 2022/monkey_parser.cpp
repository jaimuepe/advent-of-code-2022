#pragma once

#include "monkey_parser.hpp"

namespace aoc2022
{
	monkey parse_monkey(
		std::string& monkey_raw,
		std::string& starting_items_raw,
		std::string& op_raw,
		std::string& test_raw,
		std::string& if_true_raw,
		std::string& if_false_raw,
		monkey_collection& collection)
	{
		int index = parse_index(monkey_raw);

		std::vector<long double> starting_items = parse_starting_items(starting_items_raw);

		auto op = parse_op(op_raw);

		auto test = parse_test(test_raw);

		auto if_true = parse_if_true(if_true_raw, collection);

		auto if_false = parse_if_false(if_false_raw, collection);

		return monkey{ index, starting_items, op, test, if_true, if_false };
	}

	int parse_index(std::string& monkey_raw)
	{
		int index;
		sscanf_s(monkey_raw.c_str(), "Monkey %i:", &index);
		return index;
	}

	std::vector<long double> parse_starting_items(std::string& starting_items_raw)
	{
		std::vector<long double> starting_items{};

		constexpr std::string_view prefix{ "  Starting items: " };

		std::string substr = starting_items_raw.substr(prefix.size());
		auto tokens = split(substr, ',');

		for (auto& tok : tokens)
		{
			int n = atoi(tok.c_str());
			starting_items.push_back(n);
		}

		return starting_items;
	}

	std::function<long double(long double)> parse_op(std::string& op_raw)
	{
		constexpr std::string_view prefix{ "  Operation: new = " };

		std::string substr = op_raw.substr(prefix.size());
		auto tokens = split(substr, ' ');

		long double a;
		if (tokens[0] == "old")
		{
			a = std::numeric_limits<long double>().max();
		}
		else
		{
			a = atoi(tokens[0].c_str());
		}

		long double b;
		if (tokens[2] == "old")
		{
			b = std::numeric_limits<long double>().max();
		}
		else
		{
			b = atoi(tokens[2].c_str());
		}

		char op = tokens[1][0];

		return [a, b, op](long double old)
		{
			long double aa = a;
			if (aa == std::numeric_limits<long double>().max())
			{
				aa = old;
			}

			long double bb = b;
			if (bb == std::numeric_limits<long double>().max())
			{
				bb = old;
			}

			long double result;
			if (op == '+')
			{
				result = aa + bb;
			}
			else if (op == '*')
			{
				result = aa * bb;
			}
			else
			{
				std::cerr << "invalid op symbol: " << op << '\n';
				result = 0LL;
			}

			//std::cout << result << std::endl;
			return result;
		};
	}

	std::function<bool(long double)> parse_test(std::string& test_raw)
	{
		int d;
		sscanf_s(test_raw.c_str(), "  Test: divisible by %i", &d);

		return [d](long double worry_level)
		{
			//return ((long long)worry_level) % d == 0;

			//return worry_level % d == 0;
			return std::fmod(worry_level, d) == 0;
			//return worry_level % d == 0;
		};
	}

	std::function<void(int, long double)> parse_if_true(
		std::string& if_true_raw,
		monkey_collection& collection)
	{
		int monkey_id;
		sscanf_s(if_true_raw.c_str(), "    If true: throw to monkey %i", &monkey_id);

		return [&collection, monkey_id](int, long double item)
		{
			monkey& monke = collection.find(monkey_id);
			monke.add_item(item);
		};
	}

	std::function<void(int, long double)> parse_if_false(
		std::string& if_false_raw,
		monkey_collection& collection)
	{
		int monkey_id;
		sscanf_s(if_false_raw.c_str(), "    If false: throw to monkey %i", &monkey_id);

		return [&collection, monkey_id](int, long double item)
		{
			monkey& monke = collection.find(monkey_id);
			monke.add_item(item);
		};
	}
}