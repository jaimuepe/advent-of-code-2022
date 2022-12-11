#pragma once

#include <array>
#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> get_lines()
{
	std::vector<std::string> lines;

	std::string line;
	while (std::getline(std::cin, line))
	{
		lines.push_back(line);
	}

	return lines;
}

int atoi(std::string& str)
{
	return atoi(str.c_str());
}