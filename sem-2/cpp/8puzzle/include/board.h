#pragma once

#include <string>
#include <vector>

class Board
{
private:
    std::vector<std::vector<unsigned>> m_data;

public:
    static Board create_goal(unsigned size);

    static Board create_random(unsigned size);

    Board() = default;

    explicit Board(const std::vector<std::vector<unsigned>> & data);

    std::size_t size() const;

    bool is_goal() const;

    unsigned hamming() const;

    unsigned manhattan() const;

    std::string to_string() const;

    bool is_solvable() const;

    const std::vector<unsigned> & operator[](unsigned ind) const;

    friend bool operator==(const Board & lhs, const Board & rhs)
    {
        return lhs.m_data == rhs.m_data;
    }

    friend bool operator!=(const Board & lhs, const Board & rhs)
    {
        return lhs.m_data != rhs.m_data;
    }

    friend std::ostream & operator<<(std::ostream & out, const Board & board)
    {
        return out << board.to_string();
    }

    friend bool operator<(const Board & lhs, const Board & rhs)
    {

        return lhs.m_data < rhs.m_data;
    }

    void setData(unsigned i, unsigned j, unsigned value);
};
