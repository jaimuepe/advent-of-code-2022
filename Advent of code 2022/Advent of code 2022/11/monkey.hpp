#pragma once

#include <functional>
#include <vector>

namespace aoc2022
{
    struct monkey
    {
    public:
        monkey(
            int id,
            std::vector<long long> items,
            std::function<long long(long long)> op,
            std::function<bool(long long)> test,
            std::function<void(int, long long)> if_true,
            std::function<void(int, long long)> if_false);

        [[nodiscard]] int id() const { return m_id; }

        [[nodiscard]] long long inspected_items_amount() const { return m_inspected_items_amount; }

        void play();

        void add_item(long long item);

        void print_items();

    private:
        int m_id;

        long long m_inspected_items_amount{0};

        std::vector<long long> m_items;

        std::function<long long(long long)> m_op;

        std::function<bool(long long)> m_test;

        std::function<void(int, long long)> m_if_true;

        std::function<void(int, long long)> m_if_false;
    };
}
