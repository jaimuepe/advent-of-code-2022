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
            run(lines, 20);
        }

        B_IMPL()
        {
            run(lines, 10000);
        }

    private:
        static void run(std::vector<std::string> lines, const int rounds)
        {
            monkey_collection* collection = create_collection(lines);

            for (int i = 0; i < rounds; i++)
            {
                const int round = i + 1;

                for (auto& monke : collection->m_monkeys)
                {
                    monke.play(round);
                }

                if (true)
                {
                    if (round == 10 || round == 20 || round == 50 || round == 10 || round == 500)
                    {
                        std::cout << "== After round " << round << " ==\n\n";

                        for (auto& monke : collection->m_monkeys)
                        {
                            std::cout << "Monkey " << monke.id() << " inspected items " << monke.
                                inspected_items_amount() <<
                                " times.\n";
                        }
                        std::cout << "\n";
                    }
                }
            }

            std::vector<long long> inspected_items_amounts{};
            inspected_items_amounts.reserve(collection->m_monkeys.size());

            for (const auto& monke : collection->m_monkeys)
            {
                inspected_items_amounts.push_back(monke.inspected_items_amount());
            }

            std::ranges::sort(inspected_items_amounts, std::greater<>());

            const long long monkey_business = inspected_items_amounts[0] * inspected_items_amounts[1];

            print_result(monkey_business);
        }

        static monkey_collection* create_collection(std::vector<std::string>& lines)
        {
            const auto collection = new monkey_collection();

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
                    *collection);

                collection->m_monkeys.push_back(monke);
            }

            return collection;
        }
    };
}
