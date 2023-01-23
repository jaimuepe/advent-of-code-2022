#pragma once

#include "monkey.hpp"

#include <iostream>
#include <vector>

namespace aoc2022
{
    struct monkey_collection
    {
        std::vector<monkey> m_monkeys{};

        void print() const
        {
            for (auto& monke : m_monkeys)
            {
                std::cout << "Monkey " << monke.id() << ": ";
                monke.print_items();
                std::cout << '\n';
            }
            std::cout << '\n';
        }
    };
}
