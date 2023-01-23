#include "monkey.hpp"

#include <iostream>

#include "monkey_collection.h"

namespace aoc2022
{
    monkey::monkey(
        const int id,
        std::vector<int> items,
        const monkey_op op,
        const int test_division,
        const int throw_to_if_true,
        const int throw_to_if_false,
        monkey_collection* collection) :
        m_id{id},
        m_items{items.begin(), items.end()},
        m_op{op},
        m_test_division{test_division},
        m_throw_to_if_true{throw_to_if_true},
        m_throw_to_if_false{throw_to_if_false},
        m_collection{collection}
    {
        /*std::cout << "Monkey " << id << ":\n";
        std::cout << "\tItems: ";
        print_items();
        std::cout << "\top: " << op.a << " " << op.op_symbol << " " << op.b << "\n";
        std::cout << "\ttest: " << test_division << "\n";
        std::cout << "\tif true: " << throw_to_if_true << "\n";
        std::cout << "\tif false: " << throw_to_if_false << "\n";*/
    }

    void monkey::play(int)
    {
        for (long long worry_level : m_items)
        {
            m_inspected_items_amount++;

            worry_level = eval_op(worry_level);

            worry_level %= 9699690LL;

            int throw_to_index;
            if (worry_level % m_test_division == 0)
            {
                throw_to_index = m_throw_to_if_true;
            }
            else
            {
                throw_to_index = m_throw_to_if_false;
            }

            m_collection->m_monkeys[throw_to_index].add_item(worry_level);
        }

        m_items.clear();
    }

    void monkey::add_item(const long long item)
    {
        m_items.push_back(item);
    }

    void monkey::print_items() const
    {
        for (size_t i = 0; i < m_items.size(); i++)
        {
            std::cout << m_items[i];

            if (i < m_items.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "\n";
    }

    long long monkey::eval_op(const long long worry_level) const
    {
        const long long a = m_op.a == -1 ? worry_level : m_op.a;
        const long long b = m_op.b == -1 ? worry_level : m_op.b;

        if (m_op.op_symbol == '*')
        {
            return a * b;
        }
        else
        {
            return a + b;
        }
    }
}
