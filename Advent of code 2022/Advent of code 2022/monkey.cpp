#include "monkey.hpp"

#include <iostream>

namespace aoc2022
{
	monkey::monkey(
		int id,
		const std::vector<long double>& items,
		const std::function<long double(long double)>& op,
		const std::function<bool(long double)>& test,
		const std::function<void(int, long double)>& if_true,
		const std::function<void(int, long double)>& if_false) :
		m_id{ id },
		m_items{ items },
		m_op{ op },
		m_test{ test },
		m_if_true{ if_true },
		m_if_false{ if_false }
	{

	}

	void monkey::play()
	{
		for (size_t i = 0; i < m_items.size(); i++)
		{
			long double worry_level = m_items[i];

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

	void monkey::add_item(long double item)
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