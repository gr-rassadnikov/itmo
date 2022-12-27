#pragma once

#include "board.h"

class Solver
{
    class Solution
    {
    public:
        explicit Solution(std::vector<Board> moves);

        std::size_t moves() const { return m_moves.size() > 1 ? m_moves.size() - 1 : 0; }

        using const_iterator = std::vector<Board>::const_iterator;

        const_iterator begin() const { return m_moves.begin(); }

        const_iterator end() const { return m_moves.end(); }

    private:
        std::vector<Board> m_moves;
    };

private:
    static Board get_board_dx_dy(Board board, int x, int y, int dx, int dy);
    static unsigned h(const Board & board);

public:
    static Solution solve(const Board & initial);
};
