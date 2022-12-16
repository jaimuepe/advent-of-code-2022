#pragma once

#include "problem.hpp"

namespace aoc2022
{
	struct section_assignment
	{
		int min;
		int max;
	};

	class problem_04 : public problem
	{
	public:
		problem_04() : problem(4) {}

		A_IMPL()
		{
			int result = 0;

			std::vector<section_assignment> sectionAssignments{};

			for (size_t i = 0; i < lines.size(); i++)
			{
				std::string& line = lines[i];

				section_assignment first_assignment{};
				section_assignment second_assignment{};

				sscanf_s(
					line.c_str(),
					"%i-%i,%i-%i",
					&first_assignment.min,
					&first_assignment.max,
					&second_assignment.min,
					&second_assignment.max);

				if (fully_contains(first_assignment, second_assignment) ||
					fully_contains(second_assignment, first_assignment))
				{
					result++;
				}
			}

			print_result(result);
		}

		B_IMPL()
		{
			int result = 0;

			std::vector<section_assignment> sectionAssignments{};

			for (size_t i = 0; i < lines.size(); i++)
			{
				std::string& line = lines[i];

				section_assignment first_assignment{};
				section_assignment second_assignment{};

				sscanf_s(
					line.c_str(),
					"%i-%i,%i-%i",
					&first_assignment.min,
					&first_assignment.max,
					&second_assignment.min,
					&second_assignment.max);

				if (overlaps(first_assignment, second_assignment))
				{
					result++;
				}
			}

			print_result(result);
		}

	private:

		bool overlaps(section_assignment& a, section_assignment& b)
		{
			return
				a.min <= b.min && a.max >= b.min ||
				b.min <= a.min && b.max >= a.min;
		}

		bool fully_contains(section_assignment& a, section_assignment& b)
		{
			return 	a.min <= b.min && a.max >= b.max;
		}
	};
}

