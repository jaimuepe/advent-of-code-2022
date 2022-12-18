#include "grid.hpp"

#include <iostream>

template<class myType>
grid<myType>::grid(size_t rows, size_t cols) : m_rows{ rows }, m_cols{ cols }
{
	values = new myType * [m_rows];

	for (size_t i = 0; i < m_rows; i++)
	{
		values[i] = new myType[m_cols];
	}
}

template<class myType>
grid<myType>::grid(size_t rows, size_t cols, myType default_value) : grid{ rows, cols }
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			values[i][j] = default_value;
		}
	}
}

template<class myType>
void grid<myType>::print()
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