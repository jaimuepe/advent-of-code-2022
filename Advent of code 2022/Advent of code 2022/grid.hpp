#pragma once

#include <iostream>

template<class MyType>
struct grid
{
public:

	grid(size_t rows, size_t cols) : m_rows{ rows }, m_cols{ cols }
	{
		values = new MyType * [m_rows];

		for (size_t i = 0; i < m_rows; i++)
		{
			values[i] = new MyType[m_cols];
		}
	}

	grid(size_t rows, size_t cols, MyType default_value) : grid{ rows, cols }
	{
		clear(default_value);
	}

	void clear(MyType clear_value)
	{
		for (size_t i = 0; i < m_rows; i++)
		{
			for (size_t j = 0; j < m_cols; j++)
			{
				values[i][j] = clear_value;
			}
		}
	}

	inline void set(MyType value, size_t row, size_t col)
	{
		values[row][col] = value;
	}

	inline MyType get(size_t row, size_t col)
	{
		return values[row][col];
	}

	inline size_t rows() const { return m_rows; }
	inline size_t cols() const { return m_cols; }

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

	MyType** values;

	size_t m_rows;
	size_t m_cols;
};
