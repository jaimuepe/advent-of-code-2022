#pragma once

#include <iostream>

template<class myType>
struct grid
{
public:

	grid(size_t rows, size_t cols) : m_rows{ rows }, m_cols{ cols }
	{
		values = new myType * [m_rows];

		for (size_t i = 0; i < m_rows; i++)
		{
			values[i] = new myType[m_cols];
		}
	}

	grid(size_t rows, size_t cols, myType default_value) : grid{ rows, cols }
	{
		clear(default_value);
	}

	void clear(myType clear_value)
	{
		for (size_t i = 0; i < m_rows; i++)
		{
			for (size_t j = 0; j < m_cols; j++)
			{
				values[i][j] = clear_value;
			}
		}
	}

	inline void set(myType value, size_t row, size_t col)
	{
		values[row][col] = value;
	}

	inline myType get(size_t row, size_t col)
	{
		return values[row][col];
	}

	inline size_t rows() { return m_rows; }
	inline size_t cols() { return m_cols; }

	void print()
	{
		for (size_t i = 0; i < m_rows; i++)
		{
			for (size_t j = 0; j < m_cols; j++)
			{
				std::cout << values[i][j];
			}
			std::cout << '\n';
		}
	}

private:

	myType** values;

	size_t m_rows;
	size_t m_cols;
};
