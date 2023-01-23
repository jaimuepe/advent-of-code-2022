#pragma once

#include <iostream>
#include <string>

#include "monkey.hpp"
#include "monkey_collection.h"
#include "monkey_op.hpp"

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

    std::vector<int> parse_starting_items(const std::string& starting_items_raw);

    monkey_op parse_op(const std::string& op_raw);

    int parse_test(const std::string& test_raw);

    int parse_if_true(const std::string& if_true_raw);

    int parse_if_false(const std::string& if_false_raw);
}
