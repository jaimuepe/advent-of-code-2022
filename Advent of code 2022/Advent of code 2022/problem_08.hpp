#pragma once

#include "grid.hpp"
#include "problem.hpp"

namespace aoc2022
{
    struct tree_grid : grid<int>
    {
        tree_grid(const size_t rows, const size_t cols) : grid(rows, cols)
        {
        }
    };

    enum axis
    {
        HORIZONTAL,
        VERTICAL
    };

    class problem_08 final : public problem
    {
    public:
        problem_08() : problem(8)
        {
        }

        A_IMPL()
        {
            tree_grid grid = create_grid(lines);

            int result = 0;

            for (size_t i = 0; i < grid.rows(); i++)
            {
                for (size_t j = 0; j < grid.cols(); j++)
                {
                    if (is_visible(grid, i, j))
                    {
                        result++;
                    }
                }
            }

            print_result(result);
        }

        B_IMPL()
        {
            tree_grid grid = create_grid(lines);

            int best_scenic_score = -1;

            for (size_t i = 0; i < grid.rows(); i++)
            {
                for (size_t j = 0; j < grid.cols(); j++)
                {
                    best_scenic_score = std::max(best_scenic_score, get_scenic_score(grid, i, j));
                }
            }

            print_result(best_scenic_score);
        }

    private:
        static int get_scenic_score(
            tree_grid& grid,
            size_t row,
            size_t col)
        {
            int scenic_score = 1;

            scenic_score *= get_scenic_score_axis(grid, row, col, axis::HORIZONTAL);
            scenic_score *= get_scenic_score_axis(grid, row, col, axis::VERTICAL);

            return scenic_score;
        }

        static int get_scenic_score_axis(
            tree_grid& grid,
            const size_t row,
            const size_t col,
            const axis direction)
        {
            int scenic_score = 1;

            const size_t r = direction == axis::HORIZONTAL ? col : row;

            const int value = grid.get(row, col);

            int total = 0;
            for (int i = static_cast<int>(r - 1); i >= 0; i--)
            {
                total++;

                const size_t x = direction == axis::HORIZONTAL ? i : col;
                const size_t y = direction == axis::VERTICAL ? i : row;

                if (const int height = grid.get(y, x); height >= value)
                {
                    break;
                }
            }
            scenic_score *= total;

            const size_t max = direction == axis::HORIZONTAL ? grid.cols() : grid.rows();

            total = 0;
            for (size_t i = r + 1; i < max; i++)
            {
                total++;

                const size_t x = direction == axis::HORIZONTAL ? i : col;
                const size_t y = direction == axis::VERTICAL ? i : row;

                const int height = grid.get(y, x);

                if (height >= value)
                {
                    break;
                }
            }

            scenic_score *= total;
            return scenic_score;
        }

        bool is_visible(
            tree_grid& grid,
            const size_t row,
            const size_t col) const
        {
            const int n = grid.get(row, col);

            if (get_highest_tree(grid, 0, row, col, axis::VERTICAL) < n)
            {
                return true;
            }

            if (get_highest_tree(grid, row + 1, grid.rows(), col, axis::VERTICAL) < n)
            {
                return true;
            }

            if (get_highest_tree(grid, 0, col, row, axis::HORIZONTAL) < n)
            {
                return true;
            }

            if (get_highest_tree(grid, col + 1, grid.cols(), row, axis::HORIZONTAL) < n)
            {
                return true;
            }

            return false;
        }

        int get_highest_tree(
            tree_grid& grid,
            const size_t from,
            const size_t to,
            const size_t fixed,
            const axis direction) const
        {
            int highest = -1;

            for (size_t i = from; i < to; i++)
            {
                int height;

                if (direction == axis::HORIZONTAL)
                {
                    height = grid.get(fixed, i);
                }
                else
                {
                    height = grid.get(i, fixed);
                }

                highest = std::max(highest, height);
            }
            return highest;
        }

        static tree_grid create_grid(const std::vector<std::string>& lines)
        {
            const size_t cols = lines[0].size();
            const size_t rows = lines.size();

            tree_grid grid{cols, rows};

            for (size_t i = 0; i < lines.size(); i++)
            {
                auto& line = lines[i];

                for (size_t j = 0; j < line.size(); j++)
                {
                    const int val = line[j] - '0';
                    grid.set(val, i, j);
                }
            }

            return grid;
        }
    };
}
