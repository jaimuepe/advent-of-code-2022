#pragma once

#include "problem.hpp"

#include <set>

namespace aoc2022
{
#define DEBUG_PRINT false

    constexpr int A_ROPE_LENGTH = 2;
    constexpr int B_ROPE_LENGTH = 10;

    constexpr int GRID_SIZE = 35;

    struct node
    {
        int x;
        int y;

        node() : x{0}, y{0}
        {
        }

        node(int x, int y) : x{x}, y{y}
        {
        }

        bool operator<(node const& other) const
        {
            return x < other.x || (x == other.x && y < other.y);
        }
    };

    struct link
    {
        node node{};
        link* next = nullptr;
        link* prev = nullptr;
    };

    struct rope
    {
        [[nodiscard]] link* head() const { return m_head; }

        [[nodiscard]] inline link* tail() const { return m_tail; }

        explicit rope(const size_t length) : m_length{length}
        {
            auto last = new link{};
            m_tail = last;

            for (size_t i = 1; i < length; i++)
            {
                const auto new_link = new link{};

                new_link->node = node{0, 0};
                new_link->next = last;

                last->prev = new_link;

                last = new_link;
            }

            m_head = last;
        }

        void print() const
        {
            // min values for the grid
            int min_x = -5;
            int max_x = 5;
            int min_y = -5;
            int max_y = 5;

            link* link = m_head;
            while (link != nullptr)
            {
                node& n = link->node;

                min_x = std::min(min_x, n.x);
                max_x = std::max(max_x, n.x);
                min_y = std::min(min_y, n.y);
                max_y = std::max(max_y, n.y);

                link = link->next;
            }

            const size_t n_rows = max_y - min_y + 1;
            const size_t n_cols = max_x - min_x + 1;

            grid<char> grid{n_rows, n_cols, '.'};

            int i = 0;
            link = m_tail;

            const auto x_0 = static_cast<size_t>(-min_x);
            // y is mirrored
            const auto y_0 = n_rows - 1 + min_y;

            grid.set('s', y_0, x_0);

            while (link != nullptr)
            {
                const size_t x = x_0 + link->node.x;
                const size_t y = y_0 - link->node.y;

                char c;
                if (link == m_head)
                {
                    // head
                    c = 'H';
                }
                else
                {
                    // rest
                    c = '0' + static_cast<char>(m_length - 1 - i);
                }

                grid.set(c, y, x);

                link = link->prev;
                i++;
            }

            grid.print();
            std::cout << '\n';
        }

        void move(int dx, int dy)
        {
            move_internal(m_head, dx, dy);
        }

    private:
        size_t m_length;

        link* m_head;
        link* m_tail;

        void move_internal(link* link, int dx, int dy)
        {
            node& n = link->node;

            n.x += dx;
            n.y += dy;

            if (link->next)
            {
                const node& next_node = link->next->node;

                const int x_distance = std::abs(n.x - next_node.x);
                const int y_distance = std::abs(n.y - next_node.y);

                const int x_sign = n.x - next_node.x > 0 ? 1 : -1;
                const int y_sign = n.y - next_node.y > 0 ? 1 : -1;

                if (x_distance > 1 || y_distance > 1)
                {
                    if (n.x == next_node.x)
                    {
                        move_internal(link->next, 0, y_sign);
                    }
                    else if (n.y == next_node.y)
                    {
                        move_internal(link->next, x_sign, 0);
                    }
                    else
                    {
                        move_internal(link->next, x_sign, y_sign);
                    }
                }
            }
        }
    };

    class problem_09 final : public problem
    {
    public:
        problem_09() : problem(9)
        {
        }

        A_IMPL()
        {
            simulate_rope(lines, A_ROPE_LENGTH);
        }

        B_IMPL()
        {
            simulate_rope(lines, B_ROPE_LENGTH);
        }

    private:
        static void simulate_rope(const std::vector<std::string>& lines, const size_t rope_length)
        {
            rope rope{rope_length};

#if DEBUG_PRINT
			std::cout << "== Initial State ==\n\n";
			rope.print();
#endif

            std::set<node> visited_nodes{};
            visited_nodes.insert(node(0, 0));

            for (auto& line : lines)
            {
                char dir;
                int amount;

                sscanf_s(line.c_str(), "%c %i", &dir, 1, &amount);

                const int dx = dir == 'R' ? 1 : (dir == 'L' ? -1 : 0);
                const int dy = dir == 'U' ? 1 : (dir == 'D' ? -1 : 0);

                for (int j = 0; j < amount; j++)
                {
                    rope.move(dx, dy);
                    visited_nodes.insert(rope.tail()->node);
                }

#if DEBUG_PRINT
				std::cout << "== " << dir << " " << amount << " ==\n\n";
				rope.print();
#endif
            }

            print_result(visited_nodes.size());
        }
    };
}
