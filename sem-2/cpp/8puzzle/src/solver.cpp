#include "solver.h"

#include <algorithm>
#include <limits>
#include <set>

Solver::Solution::Solution(std::vector<Board> moves)
    : m_moves(std::move(moves))
{
}

Board Solver::get_board_dx_dy(Board board, int x, int y, int dx, int dy)
{
    board.setData(x, y, board[x + dx][y + dy]);
    board.setData(x + dx, y + dy, 0);
    return board;
}

unsigned Solver::h(const Board & board)
{
    if (board.size() >= 5) {
        return board.manhattan() * 10;
    }
    return board.manhattan() * 2;
}

Solver::Solution Solver::solve(const Board & initial)
{
    if (initial.is_goal()) {
        return Solution({initial});
    }
    std::vector<Board> m_data;
    std::vector<unsigned> g;
    std::vector<unsigned> parent;
    std::set<Board> used;
    std::set<unsigned> Q;
    if (!initial.is_solvable()) {
        return Solution(m_data);
    }
    m_data.push_back(initial);
    g.push_back(0);
    parent.push_back(0);
    Q.insert(0);
    unsigned current = 0;

    auto add_children = [&](const unsigned current) {
        unsigned x = 0;
        unsigned y = 0;
        for (std::size_t i = 0; i < m_data[current].size(); i++) {
            for (std::size_t j = 0; j < m_data[current].size(); j++) {
                if (m_data[current][i][j] == 0) {
                    x = i;
                    y = j;
                    break;
                }
            }
        }
        auto init = [&](const Board & new_board) {
            if (used.find(new_board) == used.end()) {
                m_data.push_back(new_board);
                Q.insert(m_data.size() - 1);
                parent.push_back(current);
                g.push_back(g[current] + 1);
                used.insert(new_board);
            }
        };
        if (x > 0) {
            init(get_board_dx_dy(m_data[current], x, y, -1, 0));
        }
        if (y > 0) {
            init(get_board_dx_dy(m_data[current], x, y, 0, -1));
        }
        if (x < m_data[current].size() - 1) {
            init(get_board_dx_dy(m_data[current], x, y, 1, 0));
        }
        if (y < m_data[current].size() - 1) {
            init(get_board_dx_dy(m_data[current], x, y, 0, 1));
        }
    };

    while (!m_data[current].is_goal()) {
        unsigned f_current = std::numeric_limits<unsigned>::max();
        for (const unsigned i : Q) {
            unsigned f = g[i] + h(m_data[i]);
            if (f < f_current) {
                current = i;
                f_current = f;
            }
        }
        add_children(current);
        Q.erase(current);
    }
    std::vector<Board> ans;
    while (current != parent[current]) {
        ans.push_back(m_data[current]);
        current = parent[current];
    }
    ans.push_back(m_data[current]);
    std::reverse(ans.begin(), ans.end());
    return Solution(ans);
}
