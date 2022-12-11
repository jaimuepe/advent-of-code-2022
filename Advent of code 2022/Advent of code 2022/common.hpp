#pragma once

#include <array>
#include <format>
#include <iostream>
#include <vector>
#include <string>

void print_title(int day, char c)
{
	std::cout << "### ADVENT OF CODE - DAY " << std::format("{:02}", day) << c << '\n' << '\n';
}

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