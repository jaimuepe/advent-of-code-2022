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
			const std::vector<long double>& items,
			const std::function<long double(long double)>& op,
			const std::function<bool(long double)>& test,
			const std::function<void(int, long double)>& if_true,
			const std::function<void(int, long double)>& if_false);

		inline int id() const { return m_id; }

		inline long double inspected_items_amount() const { return m_inspected_items_amount; }

		void play();

		void add_item(long double item);

		void print_items();

	private:

		int m_id;

		long double m_inspected_items_amount{ 0 };

		std::vector<long double> m_items;

		std::function<long double(long double)> m_op;

		std::function<bool(long double)> m_test;

		std::function<void(int, long double)> m_if_true;

		std::function<void(int, long double)> m_if_false;
	};
}

