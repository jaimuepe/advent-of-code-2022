#pragma once

#include "monkey.hpp"

#include <vector>

namespace aoc2022
{
	struct monkey_collection
	{
	public:

		inline monkey& find(int id)
		{
			return m_monkeys[id];
		}

		inline void register_monkey(monkey monkey)
		{
			m_monkeys.push_back(monkey);
		}

		inline monkey* begin() { return &m_monkeys[0]; }
		inline const monkey* begin() const { return &m_monkeys[0]; }

		inline monkey* end() { return &m_monkeys[0] + m_monkeys.size(); }
		inline const monkey* end() const { return &m_monkeys[0] + m_monkeys.size(); }

		void print()
		{
			for (auto& monke : m_monkeys)
			{
				std::cout << "Monkey " << monke.id() << ": ";
				monke.print_items();
				std::cout << '\n';
			}
			std::cout << '\n';
		}

	private:
		std::vector<monkey> m_monkeys{};
	};
}