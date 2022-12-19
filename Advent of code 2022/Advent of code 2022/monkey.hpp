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
			std::vector<int>& items,
			std::function<int(int)>& op,
			std::function<bool(int)>& test,
			std::function<void()>& if_true,
			std::function<void()> if_false);

	private:

		int m_id;

		std::vector<int> m_items;

		std::function<int(int)> m_op;

		std::function<bool(int)> m_test;

		std::function<void()> m_if_true;

		std::function<void()> m_if_false;
	};
}

