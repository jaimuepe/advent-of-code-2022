#pragma once

#include "11/monkey.hpp"
#include "11/monkey_collection.h"
#include "11/monkey_parser.hpp"
#include "problem.hpp"

#include <functional>

namespace aoc2022
{
    class problem_11 final : public problem
    {
    public:
        problem_11() : problem(11)
        {
        }

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
        static void run(monkey_collection& collection, const int rounds)
        {
            for (int i = 0; i < rounds; i++)
            {
                for (auto& monke : collection)
                {
                    monke.play();
                }

                int round = i + 1;

                if (round == 1 || round == 20 || (round > 0 && round % 1000 == 0))
                {
                    std::cout << "== After round " << round << " ==\n\n";

                    for (auto& monke : collection)
                    {
                        std::cout << "Monkey " << monke.id() << " inspected items " << monke.inspected_items_amount() <<
                            " times.\n";
                    }
                    std::cout << "\n";
                }
            }

            std::vector<long long> inspected_items_amounts{};
            for (const auto& monke : collection)
            {
                inspected_items_amounts.push_back(monke.inspected_items_amount());
            }

            std::ranges::sort(inspected_items_amounts, std::greater<>());

            const long long monkey_business = inspected_items_amounts[0] * inspected_items_amounts[1];

            print_result(monkey_business);
        }

        static monkey_collection create_collection(std::vector<std::string>& lines)
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
