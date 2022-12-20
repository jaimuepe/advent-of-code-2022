#pragma once

#include <iostream>
#include <string>

#include "monkey.hpp"
#include "monkey_collection.h"
#include "utils.hpp"

namespace aoc2022
{
	monkey parse_monkey(
		std::string& monkey_raw,
		std::string& starting_items_raw,
		std::string& op_raw,
		std::string& test_raw,
		std::string& if_true_raw,
		std::string& if_false_raw,
		monkey_collection& collection);

	int parse_index(std::string& monkey_raw);

	std::vector<long double> parse_starting_items(std::string& starting_items_raw);

	std::function<long double(long double)> parse_op(std::string& op_raw);

	std::function<bool(long double)> parse_test(std::string& test_raw);

	std::function<void(int, long double)> parse_if_true(std::string& if_true_raw, monkey_collection& collection);

	std::function<void(int, long double)> parse_if_false(std::string& if_false_raw, monkey_collection& collection);
}