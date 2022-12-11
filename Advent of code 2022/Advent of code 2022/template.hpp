#pragma once

#include "common.hpp"

namespace d0X
{
	constexpr int DAY = -1;

	namespace a
	{
		void run()
		{
			print_title(DAY, 'A');

			auto lines = get_lines();
		}
	}

	namespace b
	{
		void run()
		{
			print_title(DAY, 'B');

			auto lines = get_lines();
		}
	}
}