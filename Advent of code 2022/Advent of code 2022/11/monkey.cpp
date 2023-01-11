#include "monkey.hpp"

#include <iostream>

namespace aoc2022
{
    monkey::monkey(
        const int id,
        std::vector<long long> items,
        std::function<long long(long long)> op,
        std::function<bool(long long)> test,
        std::function<void(int, long long)> if_true,
        std::function<void(int, long long)> if_false) :
        m_id{id},
        m_items{std::move(items)},
        m_op{std::move(op)},
        m_test{std::move(test)},
        m_if_true{std::move(if_true)},
        m_if_false{std::move(if_false)}
    {
    }

    void monkey::play()
    {
        for (long long worry_level : m_items)
        {
            worry_level = m_op(worry_level);
            //worry_level /= 3;

            if (m_test(worry_level))
            {
                m_if_true(m_id, worry_level);
            }
            else
            {
                m_if_false(m_id, worry_level);
            }

            m_inspected_items_amount++;
        }

        m_items.clear();
    }

    void monkey::add_item(long long item)
    {
        m_items.push_back(item);
    }

    void monkey::print_items()
    {
        for (size_t i = 0; i < m_items.size(); i++)
        {
            std::cout << m_items[i];

            if (i < m_items.size() - 1)
            {
                std::cout << ", ";
            }
        }
    }
}
