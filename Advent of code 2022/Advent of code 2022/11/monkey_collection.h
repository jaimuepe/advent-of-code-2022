#pragma once

#include "monkey.hpp"

#include <iostream>
#include <vector>

namespace aoc2022
{
    struct monkey_collection
    {
    public:
        monkey& find(const int id)
        {
            return m_monkeys[id];
        }

        void register_monkey(const monkey monkey)
        {
            m_monkeys.push_back(monkey);
        }

        [[nodiscard]] monkey* begin() { return m_monkeys.data(); }
        [[nodiscard]] const monkey* begin() const { return m_monkeys.data(); }

        [[nodiscard]] monkey* end() { return m_monkeys.data() + m_monkeys.size(); }
        [[nodiscard]] const monkey* end() const { return m_monkeys.data() + m_monkeys.size(); }

        void print()
        {
            for (auto& monke : m_monkeys)
            {
                std::cout << "Monkey " << monke.id() << ": ";
                monke.print_items();
                std::cout << '\n';
            }
            std::cout << '\n';
        }

    private:
        std::vector<monkey> m_monkeys{};
    };
}
