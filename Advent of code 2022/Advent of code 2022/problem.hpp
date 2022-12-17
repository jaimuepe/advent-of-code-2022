#pragma once

#include <array>
#include <iostream>
#include <format>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "utils.hpp"

namespace aoc2022
{
#define A_IMPL() protected: virtual void run_a_impl(std::vector<std::string>& lines) override
#define B_IMPL() protected: virtual void run_b_impl(std::vector<std::string>& lines) override

	class problem
	{
	public:

		void run_a()
		{
			std::string filename = std::format("{:02}", m_day) + ".txt";
			auto lines = read_file(filename);

			print_title("A");
			run_a_impl(lines);
		}

		void run_b()
		{
			std::string filename = std::format("{:02}", m_day) + ".txt";
			auto lines = read_file(filename);

			print_title("B");
			run_b_impl(lines);
		}

		void run_a_test()
		{
			std::string filename = std::format("{:02}", m_day) + "_TEST.txt";
			auto lines = read_file(filename);

			print_title("A (TEST)");
			run_a_impl(lines);
		}

		void run_b_test()
		{
			std::string filename = std::format("{:02}", m_day) + "_TEST.txt";
			auto lines = read_file(filename);

			print_title("B (TEST)");
			run_b_impl(lines);
		}

	protected:

		problem(int day) : m_day{ day } {	}

		virtual void run_a_impl(std::vector<std::string>& lines) = 0;
		virtual void run_b_impl(std::vector<std::string>& lines) = 0;

		void print_title(std::string suffix)
		{
			std::cout << "### ADVENT OF CODE - DAY " << std::format("{:02}", m_day) << " " << suffix << '\n' << '\n';
		}

		template<class myType>
		void print_result(myType result)
		{
			std::cout << "Result: " << result << '\n' << '\n';
		}

	private:

		int m_day;
	};
}