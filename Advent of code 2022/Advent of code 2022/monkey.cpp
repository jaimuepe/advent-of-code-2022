#include "monkey.hpp"

namespace aoc2022
{
	monkey::monkey(
		int id,
		std::vector<int>& items,
		std::function<int(int)>& op,
		std::function<bool(int)>& test,
		std::function<void()>& if_true,
		std::function<void()> if_false) :
		m_id{ id },
		m_items{ items },
		m_op{ op },
		m_test{ test },
		m_if_true{ if_true },
		m_if_false{ if_false }
	{

	}
}