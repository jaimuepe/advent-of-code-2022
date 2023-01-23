#include "monkey_parser.hpp"
#include "../utils.hpp"

namespace aoc2022
{
    monkey parse_monkey(
        const std::string& monkey_raw,
        const std::string& starting_items_raw,
        const std::string& op_raw,
        const std::string& test_raw,
        const std::string& if_true_raw,
        const std::string& if_false_raw,
        monkey_collection& collection)
    {
        const int index = parse_index(monkey_raw);

        const std::vector<int> starting_items = parse_starting_items(starting_items_raw);

        const auto op = parse_op(op_raw);

        const int test = parse_test(test_raw);

        const int if_true = parse_if_true(if_true_raw);

        const int if_false = parse_if_false(if_false_raw);

        return monkey{index, starting_items, op, test, if_true, if_false, &collection};
    }

    int parse_index(const std::string& monkey_raw)
    {
        int index;
        sscanf_s(monkey_raw.c_str(), "Monkey %i:", &index);
        return index;
    }

    std::vector<int> parse_starting_items(const std::string& starting_items_raw)
    {
        std::vector<int> starting_items{};

        constexpr std::string_view prefix{"  Starting items: "};

        const std::string substr = starting_items_raw.substr(prefix.size());
        const auto tokens = split(substr, ',');

        for (auto& tok : tokens)
        {
            const int n = atoi(tok.c_str());
            starting_items.push_back(n);
        }

        return starting_items;
    }

    monkey_op parse_op(const std::string& op_raw)
    {
        constexpr std::string_view prefix{"  Operation: new = "};

        const std::string substr = op_raw.substr(prefix.size());
        const auto tokens = split(substr, ' ');

        int a;
        if (tokens[0] == "old")
        {
            a = -1;
        }
        else
        {
            char* p_end;
            a = strtol(tokens[0].c_str(), &p_end, 10);
        }

        int b;
        if (tokens[2] == "old")
        {
            b = -1;
        }
        else
        {
            char* p_end;
            b = strtol(tokens[2].c_str(), &p_end, 10);
        }

        const char symbol = tokens[1][0];

        monkey_op op{};
        op.op_symbol = symbol;
        op.a = a;
        op.b = b;

        return op;
    }

    int parse_test(const std::string& test_raw)
    {
        int d;
        sscanf_s(test_raw.c_str(), "  Test: divisible by %i", &d);
        return d;
    }

    int parse_if_true(const std::string& if_true_raw)
    {
        int monkey_id;
        sscanf_s(if_true_raw.c_str(), "    If true: throw to monkey %i", &monkey_id);
        return monkey_id;
    }

    int parse_if_false(const std::string& if_false_raw)
    {
        int monkey_id;
        sscanf_s(if_false_raw.c_str(), "    If false: throw to monkey %i", &monkey_id);
        return monkey_id;
    }
}
