#pragma once

#include <fstream>
#include <string>
#include <vector>

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
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				values[i][j] = default_value;
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

std::vector<std::string> read_file(std::string& file_name)
{
	std::vector<std::string> result{};

	std::ifstream ifs{ file_name };

	std::string line;
	while (std::getline(ifs, line))
	{
		result.push_back(line);
	}

	return result;
}

std::vector<std::string> split(const std::string& string, const char separator)
{
	std::vector<std::string> result{};

	std::stringstream ss{};
	bool has_token{ false };

	for (char c : string)
	{
		if (c == separator)
		{
			if (has_token)
			{
				result.push_back(ss.str());
				ss.str("");
				has_token = false;
			}
		}
		else
		{
			ss << c;
			has_token = true;
		}
	}

	if (has_token)
	{
		result.push_back(ss.str());
	}

	return result;
}