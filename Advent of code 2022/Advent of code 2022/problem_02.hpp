#pragma once

#include "problem.hpp"

namespace aoc2022
{
	constexpr int WIN_SCORE = 6;
	constexpr int DRAW_SCORE = 3;
	constexpr int LOSE_SCORE = 0;

	class problem_02 : public problem
	{
	public:
		problem_02() :problem(2) {}

	protected:

		virtual void run_a_impl(std::vector<std::string>& lines) override
		{
			int score = 0;

			for (auto& line : lines)
			{
				char a = line[0];
				char b = transform_space(line[2]);

				score += shape_score(b);
				score += play(a, b);
			}

			print_result(score);
		}

		virtual void run_b_impl(std::vector<std::string>& lines) override
		{
			int score = 0;

			for (auto& line : lines)
			{
				char a = line[0];
				char result = line[2];

				char b = calculate_play(a, result);

				score += shape_score(b);
				score += play(a, b);
			}

			print_result(score);
		}

	private:

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
			return static_cast<char>(i) + 'A';
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
	};
}