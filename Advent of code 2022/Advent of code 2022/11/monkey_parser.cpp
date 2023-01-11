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

        const std::vector<long long> starting_items = parse_starting_items(starting_items_raw);

        const auto op = parse_op(op_raw);

        const auto test = parse_test(test_raw);

        const auto if_true = parse_if_true(if_true_raw, collection);

        const auto if_false = parse_if_false(if_false_raw, collection);

        return monkey{index, starting_items, op, test, if_true, if_false};
    }

    int parse_index(const std::string& monkey_raw)
    {
        int index;
        sscanf_s(monkey_raw.c_str(), "Monkey %i:", &index);
        return index;
    }

    std::vector<long long> parse_starting_items(const std::string& starting_items_raw)
    {
        std::vector<long long> starting_items{};

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

    std::function<long long(long long)> parse_op(const std::string& op_raw)
    {
        constexpr std::string_view prefix{"  Operation: new = "};

        const std::string substr = op_raw.substr(prefix.size());
        const auto tokens = split(substr, ' ');

        long long a;
        if (tokens[0] == "old")
        {
            a = std::numeric_limits<long long>::max();
        }
        else
        {
            a = atoi(tokens[0].c_str());
        }

        long long b;
        if (tokens[2] == "old")
        {
            b = std::numeric_limits<long long>::max();
        }
        else
        {
            b = atoi(tokens[2].c_str());
        }

        char op = tokens[1][0];

        return [a, b, op](const long long old)
        {
            long long aa = a;
            if (aa == std::numeric_limits<long long>::max())
            {
                aa = old;
            }

            long long bb = b;
            if (bb == std::numeric_limits<long long>::max())
            {
                bb = old;
            }

            long long result;
            if (op == '+')
            {
                result = aa + bb;
            }
            else if (op == '*')
            {
                result = aa * bb;
            }
            else
            {
                std::cerr << "invalid op symbol: " << op << '\n';
                result = 0LL;
            }

            //std::cout << result << std::endl;
            return result;
        };
    }

    std::function<bool(long long)> parse_test(const std::string& test_raw)
    {
        int d;
        sscanf_s(test_raw.c_str(), "  Test: divisible by %i", &d);

        return [d](const long long worry_level)
        {
            return worry_level % d == 0;
        };
    }

    std::function<void(int, long long)> parse_if_true(
        const std::string& if_true_raw,
        monkey_collection& collection)
    {
        int monkey_id;
        sscanf_s(if_true_raw.c_str(), "    If true: throw to monkey %i", &monkey_id);

        return [&collection, monkey_id](int, const long long item)
        {
            monkey& monke = collection.find(monkey_id);
            monke.add_item(item);
        };
    }

    std::function<void(int, long long)> parse_if_false(
        const std::string& if_false_raw,
        monkey_collection& collection)
    {
        int monkey_id;
        sscanf_s(if_false_raw.c_str(), "    If false: throw to monkey %i", &monkey_id);

        return [&collection, monkey_id](int, const long long item)
        {
            monkey& monke = collection.find(monkey_id);
            monke.add_item(item);
        };
    }
}
