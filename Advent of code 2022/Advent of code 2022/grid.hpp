#pragma once

template<class myType>
struct grid
{
public:

	grid(size_t rows, size_t cols);

	grid(size_t rows, size_t cols, myType default_value);

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

	void print();

private:

	myType** values;

	size_t m_rows;
	size_t m_cols;
};
