#pragma once

#include <string>
#include <vector>

namespace aoc2022
{
    struct op;

    struct cpu
    {
        friend struct add_op;

        void execute(const std::vector<std::string>& args);

        inline void start_cycle() { m_cycles++; }

        void cycle() const;

        void finish_cycle();

        [[nodiscard]] int cycles() const { return m_cycles; }

        [[nodiscard]] int rx() const { return m_rx; }

        [[nodiscard]] bool has_op() const { return m_op != nullptr; }

    private:
        int m_cycles{0};

        int m_rx{1};

        op* m_op{};
    };
}
