#pragma once

#include "problem.hpp"

namespace aoc2022
{
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
			grid<int> height_grid = create_grid(lines);

			int result = 0;

			for (size_t i = 0; i < height_grid.rows(); i++)
			{
				for (size_t j = 0; j < height_grid.cols(); j++)
				{
					if (is_visible(height_grid, i, j))
					{
						result++;
					}
				}
			}

			print_result(result);
		}

		B_IMPL()
		{
			grid<int> height_grid = create_grid(lines);

			int result = 0;

			for (size_t i = 0; i < height_grid.rows(); i++)
			{
				for (size_t j = 0; j < height_grid.cols(); j++)
				{
				}
			}
		}

	private:

		int get_scenic_score(
			grid<int>& grid,
			size_t row,
			size_t col)
		{
			int scenic_score = 1;
			return 0;
		}

		bool is_visible(
			grid<int>& grid,
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
			grid<int>& grid,
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

		grid<int> create_grid(std::vector<std::string>& lines)
		{
			size_t cols = lines[0].size();
			size_t rows = lines.size();

			grid<int> grid{ cols, rows };

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

