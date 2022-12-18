#pragma once

#include "problem.hpp"

namespace aoc2022
{
	constexpr int MARKER_LENGTH_A = 4;
	constexpr int MARKER_LENGTH_B = 14;

	class problem_06 : public problem
	{
	public:
		problem_06() : problem(6) {}

		A_IMPL()
		{
			auto& line = lines[0];

			int result = get_marker_pos(line, MARKER_LENGTH_A);
			print_result(result);
		}

		B_IMPL()
		{
			auto& line = lines[0];

			int result = get_marker_pos(line, MARKER_LENGTH_B);
			print_result(result);
		}

	private:

		bool is_marker(std::string_view& view)
		{
			for (size_t i = 0; i < view.length(); i++)
			{
				for (size_t j = i + 1; j < view.length(); j++)
				{
					if (view[i] == view[j]) return false;
				}
			}

			return true;
		}

		int get_marker_pos(std::string& line, int marker_length)
		{
			int cursor = 0;

			while (cursor < line.length() - marker_length)
			{
				int from = cursor;
				int to = cursor + marker_length;

				std::string_view view{ line.begin() + from, line.begin() + to };

				if (is_marker(view))
				{
					break;
				}

				cursor++;
			}

			return cursor + marker_length;
		}

	};
}

