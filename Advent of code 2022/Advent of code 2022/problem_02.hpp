#pragma once

#include "problem.hpp"

namespace aoc2022
{
    constexpr int WIN_SCORE = 6;
    constexpr int DRAW_SCORE = 3;
    constexpr int LOSE_SCORE = 0;

    class problem_02 final : public problem
    {
    public:
        problem_02() : problem(2)
        {
        }

    protected:
        void run_a_impl(std::vector<std::string>& lines) override
        {
            int score = 0;

            for (auto& line : lines)
            {
                const char a = line[0];
                const char b = transform_space(line[2]);

                score += shape_score(b);
                score += play(a, b);
            }

            print_result(score);
        }

        void run_b_impl(std::vector<std::string>& lines) override
        {
            int score = 0;

            for (auto& line : lines)
            {
                const char a = line[0];
                const char result = line[2];

                const char b = calculate_play(a, result);

                score += shape_score(b);
                score += play(a, b);
            }

            print_result(score);
        }

    private:
        static char transform_space(char b)
        {
            return b - 'X' + 'A';
        }

        static int to_index(char c)
        {
            return c - 'A';
        }

        static char from_index(int i)
        {
            return 'A' + static_cast<char>(i);
        }

        static int shape_score(char c)
        {
            return to_index(c) + 1;
        }

        static int play(const char a, const char b)
        {
            // draw
            if (a == b) return DRAW_SCORE;

            const int a_idx = to_index(a);
            const int b_idx = to_index(b);

            if (b_idx == (a_idx + 1) % 3) return WIN_SCORE;
            return LOSE_SCORE;
        }

        static char calculate_play(const char a, const char result)
        {
            const int a_idx = to_index(a);
            int b_idx;

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
