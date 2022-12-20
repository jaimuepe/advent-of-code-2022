#pragma once

#include "monkey.hpp"
#include "monkey_collection.h"
#include "monkey_parser.hpp"
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
			monkey_collection collection = create_collection(lines);
			run(collection, 20);

		}

		B_IMPL()
		{
			monkey_collection collection = create_collection(lines);
			run(collection, 10000);
		}

	private:

		void run(monkey_collection& collection, int rounds)
		{
			for (int i = 0; i < rounds; i++)
			{
				for (auto& monke : collection)
				{
					monke.play();
				}

				/*std::cout << "== After round " << (i + 1) << " ==\n\n";

				for (auto& monke : collection)
				{
					std::cout << "Monkey " << monke.id() << " inspected items " << monke.inspected_items_amount() << " times.\n";
				}
				std::cout << "\n";*/
			}

			std::vector<long double> inspected_items_amounts{};
			for (auto& monke : collection)
			{
				inspected_items_amounts.push_back(monke.inspected_items_amount());
			}

			std::sort(inspected_items_amounts.begin(), inspected_items_amounts.end(), std::greater<long double>());

			long double  monkey_business = inspected_items_amounts[0] * inspected_items_amounts[1];

			print_result(monkey_business);
		}

		monkey_collection create_collection(std::vector<std::string>& lines)
		{
			monkey_collection collection{};

			for (size_t i = 0; i < lines.size(); i += 7)
			{
				auto& monkey_raw = lines[i];
				auto& starting_items_raw = lines[i + 1];
				auto& op_raw = lines[i + 2];
				auto& test_raw = lines[i + 3];
				auto& if_true_raw = lines[i + 4];
				auto& if_false_raw = lines[i + 5];

				monkey monke = parse_monkey(
					monkey_raw,
					starting_items_raw,
					op_raw,
					test_raw,
					if_true_raw,
					if_false_raw,
					collection);

				collection.register_monkey(monke);
			}

			return collection;
		}
	};
}

