#pragma once

#include "problem.hpp"

namespace aoc2022
{
	struct tree_grid : grid<int>
	{
		tree_grid(size_t rows, size_t cols) : grid(rows, cols) {}
	};

	enum axis
	{
		HORIZONTAL,
		VERTICAL
	};

	class problem_08 : public problem
	{
	public:
		problem_08() : problem(8) {}

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

		int get_scenic_score(
			tree_grid& grid,
			size_t row,
			size_t col)
		{
			int scenic_score = 1;

			scenic_score *= get_scenic_score_axis(grid, row, col, axis::HORIZONTAL);
			scenic_score *= get_scenic_score_axis(grid, row, col, axis::VERTICAL);

			return scenic_score;
		}

		int get_scenic_score_axis(
			tree_grid& grid,
			size_t row,
			size_t col,
			axis direction)
		{
			int scenic_score = 1;

			size_t r = direction == axis::HORIZONTAL ? col : row;

			int value = grid.get(row, col);

			int total = 0;
			for (int i = r - 1; i >= 0; i--)
			{
				total++;

				int x = direction == axis::HORIZONTAL ? i : col;
				int y = direction == axis::VERTICAL ? i : row;

				int height = grid.get(y, x);

				if (height >= value)
				{
					break;
				}

			}
			scenic_score *= total;

			int max = direction == axis::HORIZONTAL ? grid.cols() : grid.rows();

			total = 0;
			for (int i = r + 1; i < max; i++)
			{
				total++;

				int x = direction == axis::HORIZONTAL ? i : col;
				int y = direction == axis::VERTICAL ? i : row;

				int height = grid.get(y, x);

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
			size_t row,
			size_t col)
		{
			int n = grid.get(row, col);

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
			size_t from,
			size_t to,
			size_t fixed,
			axis direction)
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

		tree_grid create_grid(std::vector<std::string>& lines)
		{
			size_t cols = lines[0].size();
			size_t rows = lines.size();

			tree_grid grid{ cols, rows };

			for (size_t i = 0; i < lines.size(); i++)
			{
				auto& line = lines[i];

				for (size_t j = 0; j < line.size(); j++)
				{
					int val = line[j] - '0';
					grid.set(val, i, j);
				}
			}

			return grid;
		}
	};
}

