#include "board.h"

#include <algorithm>
#include <random>
#include <sstream>

Board Board::create_goal(const unsigned size)
{
    std::vector<std::vector<unsigned>> data_new(size);
    unsigned cnt = 0;
    for (unsigned i = 0; i < size; i++) {
        data_new[i].resize(size);
        for (unsigned j = 0; j < size; j++) {
            cnt = (cnt + 1) % (size * size);
            data_new[i][j] = cnt;
        }
    }
    return Board(data_new);
}

Board Board::create_random(const unsigned size)
{
    Board board = create_goal(size);
    std::shuffle(board.m_data.begin(), board.m_data.end(), std::mt19937(std::random_device()()));
    return board;
}

Board::Board(const std::vector<std::vector<unsigned>> & data)
    : m_data(data)
{
}

std::size_t Board::size() const
{
    return m_data.size();
}

bool Board::is_goal() const
{
    unsigned cnt = 0;
    size_t size_board = m_data.size();
    for (const std::vector<unsigned> & i : m_data) {
        for (const unsigned t : i) {
            cnt = (cnt + 1) % (size_board * size_board);
            if (t != cnt) {
                return false;
            }
        }
    }
    return true;
}

unsigned Board::hamming() const
{
    unsigned cnt = 0;
    unsigned ans = 0;
    size_t size_board = m_data.size();
    for (const std::vector<unsigned> & i : m_data) {
        for (const unsigned t : i) {
            cnt = (cnt + 1) % (size_board * size_board);
            if (t != cnt) {
                ans++;
            }
        }
    }
    return ans;
}

unsigned Board::manhattan() const
{
    unsigned ans = 0;
    size_t size_board = m_data.size();
    for (std::size_t i = 0; i < size_board; i++) {
        for (std::size_t j = 0; j < size_board; j++) {
            if (m_data[i][j] != 0) {
                ans += std::max((m_data[i][j] - 1) / size_board, i) - std::min((m_data[i][j] - 1) / size_board, i);
                ans += std::max((m_data[i][j] - 1) % size_board, j) - std::min((m_data[i][j] - 1) % size_board, j);
            }
        }
    }
    return ans;
}

std::string Board::to_string() const
{
    std::stringstream ans;
    for (const std::vector<unsigned> & i : m_data) {
        for (const unsigned t : i) {
            ans << std::to_string(t) << " ";
        }
        ans << "\n";
    }
    return ans.str();
}

bool Board::is_solvable() const
{
    unsigned ans = 0;
    int k = -1;
    size_t size_board = m_data.size();
    for (std::size_t i_f = 0; i_f < size_board; i_f++) {
        for (std::size_t j_f = 0; j_f < size_board; j_f++) {
            for (std::size_t i_s = i_f; i_s < size_board; i_s++) {
                for (std::size_t j_s = i_f == i_s ? j_f + 1 : 0; j_s < size_board; j_s++) {
                    if (m_data[i_f][j_f] > m_data[i_s][j_s] &&
                        m_data[i_f][j_f] != 0 && m_data[i_s][j_s] != 0) {
                        ans++;
                    }
                }
            }
            if (k == -1 && m_data[i_f][j_f] == 0) {
                k = (i_f + 1) % 2;
            }
        }
    }
    return (size_board % 2 == 0 && (ans + std::max(k, 0)) % 2 == 0) ||
            (size_board % 2 == 1 && ans % 2 == 0);
}
const std::vector<unsigned> & Board::operator[](const unsigned ind) const
{
    return m_data[ind];
}

void Board::setData(const unsigned i, const unsigned j, const unsigned value)
{
    m_data[i][j] = value;
}
