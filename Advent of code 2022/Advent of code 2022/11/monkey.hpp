#pragma once

#include <functional>
#include <vector>

#include "monkey_op.hpp"

namespace aoc2022
{
    struct monkey_collection;

    struct monkey
    {
    public:
        monkey(
            int id,
            std::vector<int> items,
            monkey_op op,
            int test_division,
            int throw_to_if_true,
            int throw_to_if_false,
            monkey_collection* collection);

        [[nodiscard]] int id() const { return m_id; }

        [[nodiscard]] long long inspected_items_amount() const { return m_inspected_items_amount; }

        void play(int round);

        void add_item(long long item);

        void print_items() const;

    private:
        int m_id;

        long long m_inspected_items_amount{0};

        std::vector<long long> m_items;

        monkey_op m_op;

        int m_test_division;

        int m_throw_to_if_true;

        int m_throw_to_if_false;

        monkey_collection* m_collection;

        [[nodiscard]] long long eval_op(long long worry_level) const;
    };
}
