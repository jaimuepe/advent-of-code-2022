#pragma once

#include "common.hpp"

namespace d02
{
	constexpr int WIN_SCORE = 6;
	constexpr int DRAW_SCORE = 3;
	constexpr int LOSE_SCORE = 0;

	char transform_space(char b)
	{
		return b - 'X' + 'A';
	}

	int to_index(char c)
	{
		return c - 'A';
	}

	char from_index(int i)
	{
		return i + 'A';
	}

	int shape_score(char c)
	{
		return to_index(c) + 1;
	}

	int play(char a, char b)
	{
		// draw
		if (a == b) return DRAW_SCORE;

		int a_idx = to_index(a);
		int b_idx = to_index(b);

		if (b_idx == (a_idx + 1) % 3) return WIN_SCORE;
		return LOSE_SCORE;
	}

	namespace a
	{
		void run()
		{
			print_title(2, 'A');

			auto lines = get_lines();

			int score = 0;

			for (auto& line : lines)
			{
				char a = line[0];
				char b = transform_space(line[2]);

				score += shape_score(b);
				score += play(a, b);
			}

			std::cout << score << '\n';
		}
	}

	namespace b
	{
		char calculate_play(char a, char result)
		{
			int a_idx = to_index(a);
			int b_idx = -1;

			if (result == 'X')
			{
				// lose
				if (a_idx == 0) b_idx = 2;
				else b_idx = a_idx - 1;
			}
			else if (result == 'Y')
			{
				// draw
				b_idx = a_idx;
			}
			else
			{
				// win
				b_idx = (a_idx + 1) % 3;
			}

			return from_index(b_idx);
		}

		void run()
		{
			print_title(2, 'B');

			auto lines = get_lines();

			int score = 0;

			for (auto& line : lines)
			{
				char a = line[0];
				char result = line[2];

				char b = calculate_play(a, result);

				score += shape_score(b);
				score += play(a, b);
			}

			std::cout << score << '\n';
		}
	}
}