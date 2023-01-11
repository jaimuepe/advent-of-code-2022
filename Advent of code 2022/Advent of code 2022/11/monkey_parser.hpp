#pragma once

#include <iostream>
#include <string>

#include "monkey.hpp"
#include "monkey_collection.h"

namespace aoc2022
{
    monkey parse_monkey(
        const std::string& monkey_raw,
        const std::string& starting_items_raw,
        const std::string& op_raw,
        const std::string& test_raw,
        const std::string& if_true_raw,
        const std::string& if_false_raw,
        monkey_collection& collection);

    int parse_index(const std::string& monkey_raw);

    std::vector<long long> parse_starting_items(const std::string& starting_items_raw);

    std::function<long long(long long)> parse_op(const std::string& op_raw);

    std::function<bool(long long)> parse_test(const std::string& test_raw);

    std::function<void(int, long long)> parse_if_true(const std::string& if_true_raw, monkey_collection& collection);

    std::function<void(int, long long)> parse_if_false(const std::string& if_false_raw, monkey_collection& collection);
}
