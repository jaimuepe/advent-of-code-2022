#pragma once

#include <set>
#include "problem.hpp"

namespace aoc2022
{
	constexpr int A_ROPE_LENGTH = 2;
	constexpr int B_ROPE_LENGTH = 10;

	struct node
	{
		int x{ 0 };
		int y{ 0 };

		node() {}

		node(int x, int y) : x{ x }, y{ y } {}

		bool operator<(node const& other) const {
			return x < other.x || (x == other.x && y < other.y);
		}
	};

	struct link
	{
		node node{};
		link* next;
	};

	class problem_09 : public problem
	{
	public:
		problem_09() : problem(9) {}

		A_IMPL()
		{
			simulate_rope(lines, A_ROPE_LENGTH);
		}

		B_IMPL()
		{
			simulate_rope(lines, B_ROPE_LENGTH);
		}

	private:

		void simulate_rope(std::vector<std::string>& lines, int rope_length)
		{
			link* head = create_chain(rope_length);
			link* tail = get_tail(head);

			std::set<node> visited_nodes{};
			visited_nodes.insert(node(0, 0));

			for (auto& line : lines)
			{
				char dir[1];
				int amount;

				sscanf_s(line.c_str(), "%s %i", &dir, 1, &amount);

				for (int i = 0; i < amount; i++)
				{
					move_one(head, dir);
					visited_nodes.insert(tail->node);
				}
			}

			print_result(visited_nodes.size());
		}

		link* get_tail(link* l)
		{
			link* tail = l;
			while (tail->next)
			{
				tail = tail->next;
			}
			return tail;
		}

		link* create_chain(int length)
		{
			link* tail = new link{};
			link* last = tail;

			for (int i = 1; i < length; i++)
			{
				link* new_link = new link{};

				new_link->node = node{ 0, 0 };
				new_link->next = last;

				last = new_link;
			}

			return last;
		}

		void move_one_single(link* link, std::string dir)
		{
			node& node = link->node;

			if (dir == "R")
			{
				node.x++;
			}
			else if (dir == "L")
			{
				node.x--;
			}
			else if (dir == "U")
			{
				node.y++;
			}
			else if (dir == "D")
			{
				node.y--;
			}
			else if (dir == "RU")
			{
				node.x++;
				node.y++;
			}
			else if (dir == "RD")
			{
				node.x++;
				node.y--;
			}
			else if (dir == "LU")
			{
				node.x--;
				node.y++;
			}
			else if (dir == "LD")
			{
				node.x--;
				node.y--;
			}
		}

		void move_one(link* link, std::string dir)
		{
			move_one_single(link, dir);
			node& n = link->node;

			if (link->next)
			{
				node& next_node = link->next->node;

				int h_distance = std::abs(n.x - next_node.x);
				int v_distance = std::abs(n.y - next_node.y);

				if (n.y == next_node.y && h_distance > 1)
				{
					move_one(link->next, dir);
				}
				else if (
					n.x != next_node.x &&
					n.y != next_node.y &&
					(h_distance > 1 ||
						v_distance > 1))
				{
					if (n.y > next_node.y)
					{
						move_one(link->next, dir + "U");
					}
					else
					{
						move_one(link->next, dir + "D");
					}
				}

				if (n.x == next_node.x && v_distance > 1)
				{
					move_one(link->next, dir);
				}
				else if (
					n.x != next_node.x &&
					n.y != next_node.y &&
					(h_distance > 1 ||
						v_distance > 1))
				{
					if (n.x > next_node.x)
					{
						move_one(link->next, "R" + dir);
					}
					else
					{
						move_one(link->next, "L" + dir);
					}
				}
			}
		}
	};
}

