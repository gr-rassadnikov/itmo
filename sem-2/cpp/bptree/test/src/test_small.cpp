#include "bptree.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iomanip>
#include <random>
#include <sstream>
#include <vector>

namespace {

std::mt19937_64 gen{1234567}; // NOLINT

template <class C>
void shuffle(C & c)
{
    std::shuffle(c.begin(), c.end(), gen);
}

template <std::size_t Size>
struct Dummy
{
    char data[Size];

    Dummy(const int n)
    {
        std::ostringstream ss;
        ss << std::setw(Size) << std::setfill('0') << n;
        std::memcpy(data, ss.str().c_str(), Size);
    }

    static constexpr std::size_t size()
    {
        return Size;
    }
};

template <std::size_t Size>
class Key : public Dummy<Size>
{
    using super = Dummy<Size>;
public:
    Key() : Key(-13131313) {}
    explicit Key(const int n)
        : super(n)
    {
    }

    std::ostream & print(std::ostream & strm) const
    {
        return strm << std::string_view{this->data, Size};
    }

    friend bool operator < (const Key & lhs, const Key & rhs)
    {
        return std::memcmp(lhs.data, rhs.data, Size) < 0;
    }

    friend std::ostream & operator << (std::ostream & strm, const Key & key)
    {
        return key.print(strm);
    }
};

template <std::size_t Size>
class Value : public Dummy<Size>
{
    using super = Dummy<Size>;
public:
    Value() : Value(-91919191) {}
    explicit Value(const int n)
        : super(n)
    {
    }

    std::ostream & print(std::ostream & strm) const
    {
        return strm << std::string_view{this->data, Size};
    }

    friend bool operator < (const Value & lhs, const Value & rhs)
    {
        return std::memcmp(lhs.data, rhs.data, Size) < 0;
    }

    friend std::ostream & operator << (std::ostream & strm, const Value & value)
    {
        return value.print(strm);
    }
};

class NonCopyableValue : public Dummy<16>
{
    static constexpr std::size_t Size = 16;
    using super = Dummy<Size>;
public:
    NonCopyableValue() : NonCopyableValue(-777) {}

    explicit NonCopyableValue(const int n)
        : super(n)
    {
    }

    NonCopyableValue(const NonCopyableValue &) = delete;
    NonCopyableValue(NonCopyableValue &&) = default;
    NonCopyableValue & operator = (const NonCopyableValue &) = delete;
    NonCopyableValue & operator = (NonCopyableValue &&) = default;

    std::ostream & print(std::ostream & strm) const
    {
        return strm << std::string_view{data, Size};
    }

    friend std::ostream & operator << (std::ostream & strm, const NonCopyableValue & value)
    {
        return value.print(strm);
    }
};

struct BPTree_3 : ::testing::Test
{
    using K = Key<8>;
    using V = Value<8>;

    static constexpr std::size_t Overhead = sizeof(std::size_t) + sizeof(void *);
    static constexpr std::size_t InternalCount = 3;
    static constexpr std::size_t BlockSize = InternalCount * sizeof(std::pair<K, void *>) + Overhead;

    BPTree<K, V, BlockSize> tree;

    static K create_key(const int n)
    {
        return K{n};
    }

    static V create_value(const int n)
    {
        return V{n};
    }

    inline static const V s_empty_value;

    static int cmp(const K & lhs, const K & rhs)
    {
        return std::memcmp(lhs.data, rhs.data, lhs.size());
    }

    static int cmp(const V & lhs, const V & rhs)
    {
        return std::memcmp(lhs.data, rhs.data, lhs.size());
    }
};

struct BPTree_3_descending : ::testing::Test
{
    using K = Key<5>;
    using V = Value<3>;

    struct Cmp
    {
        bool operator () (const K & lhs, const K & rhs) const
        {
            return rhs < lhs;
        }
    };

    static constexpr std::size_t Overhead = sizeof(std::size_t) + sizeof(void *);
    static constexpr std::size_t InternalCount = 3;
    static constexpr std::size_t BlockSize = InternalCount * sizeof(std::pair<K, void *>) + Overhead;

    BPTree<K, V, BlockSize, Cmp> tree;

    static K create_key(const int n)
    {
        return K{n};
    }

    static V create_value(const int n)
    {
        return V{n};
    }

    inline static const V s_empty_value;

    static int cmp(const K & lhs, const K & rhs)
    {
        return std::memcmp(lhs.data, rhs.data, lhs.size());
    }

    static int cmp(const V & lhs, const V & rhs)
    {
        return std::memcmp(lhs.data, rhs.data, lhs.size());
    }
};

struct BPTree_3_non_copyable_values : ::testing::Test
{
    using K = Key<8>;
    using V = NonCopyableValue;

    static constexpr std::size_t Overhead = sizeof(std::size_t) + sizeof(void *);
    static constexpr std::size_t InternalCount = 3;
    static constexpr std::size_t BlockSize = InternalCount * sizeof(std::pair<K, void *>) + Overhead;

    BPTree<K, V, BlockSize> tree;

    static K create_key(const int n)
    {
        return K{n};
    }

    static V create_value(const int n)
    {
        return V{n};
    }
};

} // anonymous namespace

TEST_F(BPTree_3, empty)
{
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(0, tree.size());
    EXPECT_FALSE(tree.contains(create_key(1)));
    EXPECT_FALSE(tree.contains(create_key(7)));
    EXPECT_EQ(0, tree.count(create_key(13)));
    EXPECT_EQ(tree.begin(), tree.end());
    {
        const auto [b, e] = tree.equal_range(create_key(11));
        EXPECT_EQ(b, e);
        EXPECT_EQ(tree.end(), e);
    }
    {
        const auto l = tree.lower_bound(create_key(3));
        const auto u = tree.lower_bound(create_key(3));
        EXPECT_EQ(l, u);
        EXPECT_EQ(l, tree.end());
    }
    {
        const auto it = static_cast<const decltype(tree) &>(tree).find(create_key(5));
        EXPECT_EQ(tree.end(), it);
    }
    tree.clear();
    EXPECT_EQ(tree.begin(), tree.end());
}

TEST_F(BPTree_3, singleton)
{
    decltype(tree) another{std::pair<K, V>{create_key(17), create_value(34)}};
    EXPECT_FALSE(another.empty());
    EXPECT_EQ(1, another.size());
    EXPECT_EQ(1, another.count(create_key(17)));
    EXPECT_EQ(0, another.count(create_key(11)));
    EXPECT_EQ(0, another.count(create_key(19)));
    EXPECT_TRUE(another.contains(create_key(17)));
    EXPECT_FALSE(another.contains(create_key(16)));
    EXPECT_FALSE(another.contains(create_key(0)));
    EXPECT_FALSE(another.contains(K{}));
    EXPECT_EQ(another.end(), another.find(create_key(1)));
    EXPECT_EQ(another.end(), another.find(create_key(7)));
    EXPECT_EQ(another.end(), another.find(create_key(19)));
    {
        auto [b, e] = static_cast<const decltype(another) &>(another).equal_range(create_key(17));
        EXPECT_NE(another.end(), b);
        EXPECT_NE(b, e);
        EXPECT_EQ(another.end(), e);
        EXPECT_EQ(0, cmp(b->first, create_key(17)));
        EXPECT_EQ(0, cmp(b->second, create_value(34)));
        ++b;
        EXPECT_EQ(b, e);
    }
    {
        auto it = another.begin();
        EXPECT_NE(another.end(), it);
        EXPECT_EQ(0, cmp(it->first, create_key(17)));
        EXPECT_EQ(0, cmp(it->second, create_value(34)));
        ++it;
        EXPECT_EQ(another.end(), it);
    }
    {
        auto it = another.find(create_key(17));
        EXPECT_NE(another.end(), it);
        EXPECT_EQ(0, cmp(it->first, create_key(17)));
        EXPECT_EQ(0, cmp(it->second, create_value(34)));
        ++it;
        EXPECT_EQ(another.end(), it);
    }
    for (auto & [k, v] : another) {
        EXPECT_EQ(0, cmp(k, create_key(17)));
        v.data[0] = '@';
    }
    {
        auto x = create_value(34);
        x.data[0] = '@';
        const auto & v = another.at(create_key(17));
        EXPECT_EQ(0, cmp(x, v));
    }
    another.clear();
    EXPECT_EQ(0, another.size());
    EXPECT_TRUE(another.empty());
    EXPECT_FALSE(another.contains(create_key(17)));
}

TEST_F(BPTree_3, fill_three_levels__index_operator)
{
    std::vector<std::pair<K, V>> contents;
    contents.reserve(10);
    contents.emplace_back(create_key(29), s_empty_value);
    EXPECT_EQ(0, cmp(contents.back().second, tree[contents.back().first]));
    contents.emplace_back(create_key(41), create_value(111));
    tree[contents.back().first] = contents.back().second;
    contents.emplace_back(create_key(7), create_value(5));
    tree[contents.back().first] = contents.back().second;
    contents.emplace_back(create_key(17), s_empty_value);
    tree[contents.back().first];
    contents.emplace_back(create_key(12), create_value(-1001));
    tree[contents.back().first] = contents.back().second;
    contents.emplace_back(create_key(1), create_value(0));
    tree[contents.back().first] = contents.back().second;
    contents.emplace_back(create_key(8), s_empty_value);
    tree[contents.back().first] = contents.back().second;
    contents.emplace_back(create_key(10), create_value(99999));
    tree[contents.back().first] = contents.back().second;
    contents.emplace_back(create_key(9), s_empty_value);
    tree[contents.back().first];
    contents.emplace_back(create_key(11), create_value(3456));
    tree[contents.back().first] = contents.back().second;
    contents.emplace_back(create_key(31), create_value(11111));
    tree[contents.back().first] = contents.back().second;
    contents.emplace_back(create_key(37), create_value(222));
    tree[contents.back().first] = contents.back().second;
    contents.emplace_back(create_key(35), create_value(-777));
    tree[contents.back().first] = contents.back().second;
    contents.emplace_back(create_key(25), create_value(1234));
    tree[contents.back().first] = contents.back().second;
    contents.emplace_back(create_key(27), create_value(987));
    tree[contents.back().first] = contents.back().second;
    contents.emplace_back(create_key(33), create_value(55));
    tree[contents.back().first] = contents.back().second;
    contents.emplace_back(create_key(2), create_value(1));
    tree[contents.back().first] = contents.back().second;
    contents.emplace_back(create_key(3), create_value(2));
    tree[contents.back().first] = contents.back().second;

    std::sort(contents.begin(), contents.end());
    const auto [c_end, t_end] = std::mismatch(contents.begin(), contents.end(), tree.begin(), tree.end(),
        [] (const auto & lhs, const auto & rhs) {
            return 0 == cmp(lhs.first, rhs.first) && 0 == cmp(lhs.second, rhs.second);
        });
    EXPECT_EQ(contents.end(), c_end) << "difference at " << std::distance(contents.begin(), c_end) << " with <" << c_end->first << ", " << c_end->second << ">";
    EXPECT_EQ(tree.end(), t_end) << "difference at " << std::distance(tree.begin(), t_end) << " with <" << t_end->first << ", " << t_end->second << ">";
}

TEST_F(BPTree_3, fill_three_levels__sorted__insert)
{
    std::vector<std::pair<K, V>> contents;
    contents.reserve(27);
    tree[create_key(0)];
    for (int i = -10; i < 17; ++i) {
        if (i == 0) {
            contents.emplace_back(create_key(0), s_empty_value);
            continue;
        }
        auto & x = contents.emplace_back(create_key(i), create_value(i * i));
        const auto [it, inserted] = tree.insert(x.first, x.second);
        ASSERT_TRUE(inserted);
        EXPECT_EQ(0, cmp(x.first, it->first));
        EXPECT_EQ(0, cmp(x.second, it->second));
    }

    std::sort(contents.begin(), contents.end());
    const auto [c_end, t_end] = std::mismatch(contents.begin(), contents.end(), tree.begin(), tree.end(),
        [] (const auto & lhs, const auto & rhs) {
            return 0 == cmp(lhs.first, rhs.first) && 0 == cmp(lhs.second, rhs.second);
        });
    EXPECT_EQ(contents.end(), c_end) << "difference at " << std::distance(contents.begin(), c_end) << " with <" << c_end->first << ", " << c_end->second << ">";
    EXPECT_EQ(tree.end(), t_end) << "difference at " << std::distance(tree.begin(), t_end) << " with <" << t_end->first << ", " << t_end->second << ">";
}

TEST_F(BPTree_3, fill_three_levels__backward_sorted__insert_range)
{
    std::vector<std::pair<K, V>> contents;
    contents.reserve(27);
    for (int i = 16; i > -11; --i) {
        contents.emplace_back(create_key(i), create_value(i * 2));
    }
    tree.insert(contents.begin(), contents.end());

    std::sort(contents.begin(), contents.end());
    const auto [c_end, t_end] = std::mismatch(contents.begin(), contents.end(), tree.begin(), tree.end(),
        [] (const auto & lhs, const auto & rhs) {
            return 0 == cmp(lhs.first, rhs.first) && 0 == cmp(lhs.second, rhs.second);
        });
    EXPECT_EQ(contents.end(), c_end) << "difference at " << std::distance(contents.begin(), c_end) << " with <" << c_end->first << ", " << c_end->second << ">";
    EXPECT_EQ(tree.end(), t_end) << "difference at " << std::distance(tree.begin(), t_end) << " with <" << t_end->first << ", " << t_end->second << ">";
}

TEST_F(BPTree_3, copy)
{
    std::vector<std::pair<K, V>> contents;
    contents.reserve(27);
    for (int i = 0; i < 27; ++i) {
        contents.emplace_back(create_key(i), create_value(i * 3));
    }
    shuffle(contents);
    tree.insert(contents.begin(), contents.end());

    std::sort(contents.begin(), contents.end());
    {
        const auto [c_end, t_end] = std::mismatch(contents.begin(), contents.end(), tree.begin(), tree.end(),
                [] (const auto & lhs, const auto & rhs) {
                return 0 == cmp(lhs.first, rhs.first) && 0 == cmp(lhs.second, rhs.second);
            });
        EXPECT_EQ(contents.end(), c_end) << "difference at " << std::distance(contents.begin(), c_end) << " with <" << c_end->first << ", " << c_end->second << ">";
        EXPECT_EQ(tree.end(), t_end) << "difference at " << std::distance(tree.begin(), t_end) << " with <" << t_end->first << ", " << t_end->second << ">";
    }

    auto copy = tree;
    {
        const auto [c_end, t_end] = std::mismatch(copy.begin(), copy.end(), tree.begin(), tree.end(),
                [] (const auto & lhs, const auto & rhs) {
                return 0 == cmp(lhs.first, rhs.first) && 0 == cmp(lhs.second, rhs.second);
            });
        EXPECT_EQ(copy.end(), c_end) << "difference at " << std::distance(copy.begin(), c_end) << " with <" << c_end->first << ", " << c_end->second << ">";
        EXPECT_EQ(tree.end(), t_end) << "difference at " << std::distance(tree.begin(), t_end) << " with <" << t_end->first << ", " << t_end->second << ">";
    }

    tree.erase(create_key(11));
    tree.erase(tree.find(create_key(21)));
    tree.erase(tree.lower_bound(create_key(13)), tree.lower_bound(create_key(17)));
    std::vector<std::pair<K, V>> new_contents;
    new_contents.reserve(21);
    for (int i = 0; i < 11; ++i) {
        new_contents.emplace_back(create_key(i), create_value(i * 3));
    }
    new_contents.emplace_back(create_key(12), create_value(12 * 3));
    for (int i = 17; i < 21; ++i) {
        new_contents.emplace_back(create_key(i), create_value(i * 3));
    }
    for (int i = 22; i < 27; ++i) {
        new_contents.emplace_back(create_key(i), create_value(i * 3));
    }

    {
        const auto [c_end, t_end] = std::mismatch(contents.begin(), contents.end(), copy.begin(), copy.end(),
                [] (const auto & lhs, const auto & rhs) {
                return 0 == cmp(lhs.first, rhs.first) && 0 == cmp(lhs.second, rhs.second);
            });
        EXPECT_EQ(contents.end(), c_end) << "difference at " << std::distance(contents.begin(), c_end) << " with <" << c_end->first << ", " << c_end->second << ">";
        EXPECT_EQ(copy.end(), t_end) << "difference at " << std::distance(copy.begin(), t_end) << " with <" << t_end->first << ", " << t_end->second << ">";
    }
    {
        const auto [c_end, t_end] = std::mismatch(new_contents.begin(), new_contents.end(), tree.begin(), tree.end(),
                [] (const auto & lhs, const auto & rhs) {
                return 0 == cmp(lhs.first, rhs.first) && 0 == cmp(lhs.second, rhs.second);
            });
        EXPECT_EQ(new_contents.end(), c_end) << "difference at " << std::distance(new_contents.begin(), c_end) << " with <" << c_end->first << ", " << c_end->second << ">";
        EXPECT_EQ(tree.end(), t_end) << "difference at " << std::distance(tree.begin(), t_end) << " with <" << t_end->first << ", " << t_end->second << ">";
    }
}

TEST_F(BPTree_3, move)
{
    std::vector<std::pair<K, V>> contents;
    contents.reserve(31);
    for (int i = 0; i < 31; ++i) {
        contents.emplace_back(create_key(i), create_value(i * 3));
    }
    shuffle(contents);
    tree.insert(contents.begin(), contents.end());

    std::sort(contents.begin(), contents.end());
    {
        const auto [c_end, t_end] = std::mismatch(contents.begin(), contents.end(), tree.begin(), tree.end(),
                [] (const auto & lhs, const auto & rhs) {
                return 0 == cmp(lhs.first, rhs.first) && 0 == cmp(lhs.second, rhs.second);
            });
        EXPECT_EQ(contents.end(), c_end) << "difference at " << std::distance(contents.begin(), c_end) << " with <" << c_end->first << ", " << c_end->second << ">";
        EXPECT_EQ(tree.end(), t_end) << "difference at " << std::distance(tree.begin(), t_end) << " with <" << t_end->first << ", " << t_end->second << ">";
    }

    auto move = std::move(tree);
    {
        const auto [c_end, t_end] = std::mismatch(contents.begin(), contents.end(), move.begin(), move.end(),
                [] (const auto & lhs, const auto & rhs) {
                return 0 == cmp(lhs.first, rhs.first) && 0 == cmp(lhs.second, rhs.second);
            });
        EXPECT_EQ(contents.end(), c_end) << "difference at " << std::distance(contents.begin(), c_end) << " with <" << c_end->first << ", " << c_end->second << ">";
        EXPECT_EQ(move.end(), t_end) << "difference at " << std::distance(move.begin(), t_end) << " with <" << t_end->first << ", " << t_end->second << ">";
    }

    tree = {std::make_pair(create_key(111), create_value(-111)), std::make_pair(create_key(333), create_value(-333)), std::make_pair(create_key(777), create_value(-777))};
    {
        const auto [c_end, t_end] = std::mismatch(contents.begin(), contents.end(), move.begin(), move.end(),
                [] (const auto & lhs, const auto & rhs) {
                return 0 == cmp(lhs.first, rhs.first) && 0 == cmp(lhs.second, rhs.second);
            });
        EXPECT_EQ(contents.end(), c_end) << "difference at " << std::distance(contents.begin(), c_end) << " with <" << c_end->first << ", " << c_end->second << ">";
        EXPECT_EQ(move.end(), t_end) << "difference at " << std::distance(move.begin(), t_end) << " with <" << t_end->first << ", " << t_end->second << ">";
    }
}

TEST_F(BPTree_3, erase)
{
    std::vector<std::pair<K, V>> contents;
    contents.reserve(27);
    const auto add = [&] (const int n) {
        auto & x = contents.emplace_back(create_key(n), create_value(-n));
        tree[x.first] = x.second;
    };
    const auto remove = [&] (const int n) {
        contents.erase(std::remove_if(contents.begin(), contents.end(), [x = create_key(n)] (const auto & v) {
                return 0 == cmp(x, v.first);
            }), contents.end());
        tree.erase(create_key(n));
    };
#define CHECK \
    std::sort(contents.begin(), contents.end()); \
    { \
        const auto [c_end, t_end] = std::mismatch(contents.begin(), contents.end(), tree.begin(), tree.end(), \
                [] (const auto & lhs, const auto & rhs) { \
                    return 0 == cmp(lhs.first, rhs.first) && 0 == cmp(lhs.second, rhs.second); \
            }); \
        EXPECT_EQ(contents.end(), c_end) << "difference at " << std::distance(contents.begin(), c_end) << " with <" << c_end->first << ", " << c_end->second << ">"; \
        EXPECT_EQ(tree.end(), t_end) << "difference at " << std::distance(tree.begin(), t_end) << " with <" << t_end->first << ", " << t_end->second << ">"; \
    }

    add(20);
    add(29);
    add(7);
    CHECK
    remove(20);
    CHECK
    add(11);
    add(13);
    add(1);
    add(9);
    CHECK
    add(8);
    add(12);
    add(14);
    CHECK
    remove(7);
    remove(8);
    remove(9);
    CHECK
    remove(13);
    remove(29);
    CHECK
    add(19);
    add(21);
    CHECK
    add(5);
    add(7);
    CHECK
    remove(11);
    remove(12);
    remove(14);
    remove(7);
    remove(1);
    CHECK
    add(0);
    CHECK
    add(42);
    add(4);
    add(2);
    add(10);
    add(13);
    add(9);
    CHECK
    add(8);
    add(6);
    add(1);
    add(3);
    CHECK
    add(11);
    add(12);
    add(14);
    add(17);
    add(30);
    add(37);
    CHECK
    remove(2);
    remove(4);
    remove(0);
    remove(1);
    remove(3);
    remove(12);
    remove(13);
    remove(14);
    remove(37);
    CHECK
    add(38);
    add(49);
    CHECK
    remove(11);
    remove(42);
    remove(49);
    CHECK
    remove(6);
    remove(8);
    CHECK
    remove(5);
    remove(19);
    remove(17);
    CHECK
    add(15);
    CHECK
    remove(9);
    remove(10);
    CHECK
    add(19);
    CHECK
    add(20);
    add(24);
    add(27);
    CHECK
    add(29);
    add(33);
    add(37);
    CHECK
}

TEST_F(BPTree_3_descending, small_range)
{
    const int max = 6;
    std::vector<std::pair<K, V>> contents;
    contents.reserve(max);
    for (int i = 0; i < max; ++i) {
        contents.emplace_back(create_key(i), create_value(i * i));
    }
    shuffle(contents);
    tree.insert(contents.begin(), contents.end());

    std::sort(contents.begin(), contents.end(), [cmp = Cmp{}] (const auto & lhs, const auto & rhs) {
            return cmp(lhs.first, rhs.first);
        });
    {
        const auto [c_end, t_end] = std::mismatch(contents.begin(), contents.end(), tree.begin(), tree.end(),
            [] (const auto & lhs, const auto & rhs) {
                return 0 == cmp(lhs.first, rhs.first) && 0 == cmp(lhs.second, rhs.second);
            });
        EXPECT_EQ(contents.end(), c_end) << "difference at " << std::distance(contents.begin(), c_end) << " with <" << c_end->first << ", " << c_end->second << ">";
        EXPECT_EQ(tree.end(), t_end) << "difference at " << std::distance(tree.begin(), t_end) << " with <" << t_end->first << ", " << t_end->second << ">";
    }
}

TEST_F(BPTree_3_descending, medium_range)
{
    const int max = 18;
    std::vector<std::pair<K, V>> contents;
    contents.reserve(max);
    for (int i = 0; i < max; ++i) {
        contents.emplace_back(create_key(i), create_value(i * i));
    }
    shuffle(contents);
    tree.insert(contents.begin(), contents.end());

    std::sort(contents.begin(), contents.end(), [cmp = Cmp{}] (const auto & lhs, const auto & rhs) {
            return cmp(lhs.first, rhs.first);
        });
    {
        const auto [c_end, t_end] = std::mismatch(contents.begin(), contents.end(), tree.begin(), tree.end(),
            [] (const auto & lhs, const auto & rhs) {
                return 0 == cmp(lhs.first, rhs.first) && 0 == cmp(lhs.second, rhs.second);
            });
        EXPECT_EQ(contents.end(), c_end) << "difference at " << std::distance(contents.begin(), c_end) << " with <" << c_end->first << ", " << c_end->second << ">";
        EXPECT_EQ(tree.end(), t_end) << "difference at " << std::distance(tree.begin(), t_end) << " with <" << t_end->first << ", " << t_end->second << ">";
    }
}

TEST_F(BPTree_3_descending, large_range)
{
    const int max = 54;
    std::vector<std::pair<K, V>> contents;
    contents.reserve(max);
    for (int i = 0; i < max; ++i) {
        contents.emplace_back(create_key(i), create_value(i * i));
    }
    shuffle(contents);
    tree.insert(contents.begin(), contents.end());

    std::sort(contents.begin(), contents.end(), [cmp = Cmp{}] (const auto & lhs, const auto & rhs) {
            return cmp(lhs.first, rhs.first);
        });
    {
        const auto [c_end, t_end] = std::mismatch(contents.begin(), contents.end(), tree.begin(), tree.end(),
            [] (const auto & lhs, const auto & rhs) {
                return 0 == cmp(lhs.first, rhs.first) && 0 == cmp(lhs.second, rhs.second);
            });
        EXPECT_EQ(contents.end(), c_end) << "difference at " << std::distance(contents.begin(), c_end) << " with <" << c_end->first << ", " << c_end->second << ">";
        EXPECT_EQ(tree.end(), t_end) << "difference at " << std::distance(tree.begin(), t_end) << " with <" << t_end->first << ", " << t_end->second << ">";
    }
}

TEST_F(BPTree_3_non_copyable_values, insert)
{
    for (int i = 0; i < 100; ++i) {
        tree.insert(create_key(i), create_value(i * i));
    }
}
