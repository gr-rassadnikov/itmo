#include "bptree.h"
#include "test_iterator.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <iomanip>
#include <map>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

namespace {

std::mt19937_64 rgen(13151719); // NOLINT

struct BigOne
{
    std::array<unsigned char, 2032> data;

    BigOne()
    {
        data.fill(0);
    }

    BigOne(const int x)
    {
        data.fill(0);
        std::ostringstream ss;
        ss << std::setw(data.size() / 2) << std::setfill('0') << x;
        auto str = ss.str();
        std::copy(str.begin(), str.end(), data.begin());
    }

    operator int () const
    {
        return std::stoi(std::string(data.begin(), data.end()));
    }

    friend std::ostream & operator << (std::ostream & strm, const BigOne & x)
    {
        return strm << static_cast<int>(x);
    }

    friend bool operator == (const BigOne & lhs, const BigOne & rhs)
    {
        return lhs.data == rhs.data;
    }

    friend bool operator != (const BigOne & lhs, const BigOne & rhs)
    {
        return !(lhs == rhs);
    }
};

template <class T>
struct IntCompat
{
    static T create(const int x)
    { return x; }
    static int value(const T & x)
    { return x; }
    static bool empty(const T & x)
    { return x == T{}; }
};

template <>
struct IntCompat<std::string>
{
    static constexpr std::size_t width = 10;
    static std::string create(const int x)
    {
        std::ostringstream ss;
        ss << std::setw(width) << std::setfill('0') << x;
        return ss.str();
    }
    static int value(const std::string & x)
    { return std::stoi(x); }
    static bool empty(const std::string & x)
    { return x.empty(); }
};

template <class Key, class Value>
struct Type
{
    using key_type = Key;
    using value_type = Value;

    static std::pair<Key, Value> create(const int x)
    { return {create_key(x), create_value(x)}; }
    static Key create_key(const int x)
    { return IntCompat<Key>::create(x); }
    static Value create_value(const int x)
    { return IntCompat<Value>::create(x); }

    static int key(const Key & x)
    { return IntCompat<Key>::value(x); }
    static int key(const std::pair<const Key, Value> & x)
    { return IntCompat<Key>::value(x.first); }
    static int value(const std::pair<const Key, Value> & x)
    { return IntCompat<Value>::value(x.second); }
    static int value(const Value & x)
    { return IntCompat<Value>::value(x); }

    static bool empty_value(const Value & v)
    { return IntCompat<Value>::empty(v); }
};

template <class T>
struct BPTreeTest : ::testing::Test
{
    using Tree = BPTree<typename T::key_type, typename T::value_type>;
    Tree tree;

    const Tree & const_tree()
    {
        return tree;
    }

    void insert(const std::pair<typename T::key_type, typename T::value_type> & el)
    {
        tree.insert(el.first, el.second);
    }

    using iterator_t = typename Tree::iterator;

    Tree & not_empty_container()
    {
        if (tree.empty()) {
            tree.insert(T::create_key(111), T::create_value(111));
            tree.insert(T::create_key(2331), T::create_value(2331));
            tree.insert(T::create_key(13999), T::create_value(13999));
            tree.insert(T::create_key(97777), T::create_value(97777));
            tree.insert(T::create_key(131111), T::create_value(131111));
        }
        return tree;
    }
};

using TestedTypes = ::testing::Types<Type<int, std::string>, Type<std::string, int>, Type<std::string, std::string>, Type<int, BigOne>>;
TYPED_TEST_SUITE(BPTreeTest, TestedTypes);

} // anonymous namespace

TEST(BPTreeBasicTest, copy_construct)
{
    using Tree = BPTree<int, std::string>;
    auto first = std::make_unique<Tree>();
    const int max = 11317;
    for (int i = 0; i < max; ++i) {
        first->insert(i, std::to_string(i));
    }
    Tree second = *first;
    first.reset();
    for (int i = max; i > 0; --i) {
        EXPECT_EQ(std::to_string(i-1), second[i-1]);
        second[i-1] += '@';
    }
    Tree third = second;
    for (auto & [k, v] : third) {
        v += "#####";
    }
    for (const auto & [k, v] : second) {
        const std::string expected = std::to_string(k) + '@';
        EXPECT_EQ(expected, v);
    }
}

TEST(BPTreeBasicTest, copy_assign)
{
    const int max = 10711;
    using Tree = BPTree<int, std::string>;
    Tree second, third;
    third.insert(-111, "Foo");
    third.insert(-111222, "Bar");
    third.insert(-1, "Baz");
    {
        Tree first;
        for (int i = 0; i < max; ++i) {
            first.insert(i, std::to_string(i));
        }
        second = first;
    }
    for (int i = max; i > 0; --i) {
        EXPECT_EQ(std::to_string(i-1), second[i-1]);
    }
    third = second;
    EXPECT_EQ(second.size(), third.size());
    EXPECT_FALSE(third.contains(-1));
    EXPECT_FALSE(third.contains(-111));
    for (int i = 0; i < max/2; ++i) {
        second.erase(i);
    }
    EXPECT_EQ(max - max/2, second.size());
    EXPECT_FALSE(second.contains(11));
    EXPECT_TRUE(third.contains(11));
    EXPECT_EQ(std::to_string(1111), third.at(1111));
}

TEST(BPTreeBasicTest, move_construct)
{
    using Tree = BPTree<int, std::string>;
    const int max = 17293;
    auto first = std::make_unique<Tree>();
    for (int i = 0; i < max; ++i) {
        first->insert(i, std::to_string(i));
    }
    Tree second = std::move(*first);
    first.reset();
    EXPECT_EQ(max, second.size());
    for (int i = max; i > 0; --i) {
        auto it = second.find(i-1);
        EXPECT_NE(it, second.end());
        EXPECT_EQ(i-1, it->first);
        EXPECT_EQ(std::to_string(i-1), it->second);
    }
    Tree third;
    third.insert(-1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    third.insert(-2, "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
    third.insert(-3, "cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc");
    third.insert(111, "ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");
    Tree fourth = std::move(second);
    second = third;
    for (int i = 0; i < max; ++i) {
        EXPECT_TRUE(fourth.contains(i));
        EXPECT_EQ(std::to_string(i), fourth[i]);
    }
    EXPECT_EQ("aaaaaa", second[-1].substr(0, 6));
    EXPECT_EQ("ccc", second[-3].substr(9, 3));
    EXPECT_EQ("ddddd", second[111].substr(11, 5));
}

TEST(BPTreeBasicTest, move_assign)
{
    using Tree = BPTree<std::string, int>;
    const int max = 15601;
    Tree first, second, third;
    for (int i = 0; i < max; ++i) {
        first.insert(std::to_string(i), i);
    }
    EXPECT_EQ(max, first.size());
    for (int i = 0; i < 991; ++i) {
        second.insert(std::to_string(i), i);
    }
    EXPECT_EQ(991, second.size());
    for (int i = -max; i < 0; ++i) {
        third.insert(std::to_string(i), i);
    }
    EXPECT_EQ(max, third.size());
    second = std::move(first);
    first = third;
    EXPECT_EQ(max, second.size());
    for (int i = max; i > 0; --i) {
        auto it = second.find(std::to_string(i-1));
        EXPECT_NE(second.end(), it);
        EXPECT_EQ(std::to_string(i-1), it->first);
        EXPECT_EQ(i-1, it->second);
    }
    EXPECT_EQ(max, first.size());
    for (const auto & [k, v] : third) {
        EXPECT_TRUE(first.contains(k));
        EXPECT_EQ(v, first[k]);
    }
}

TYPED_TEST(BPTreeTest, count)
{
    this->insert(TypeParam::create(7));
    EXPECT_EQ(0, this->const_tree().count(TypeParam::create_key(6)));
    EXPECT_EQ(1, this->tree.count(TypeParam::create_key(7)));
}

TYPED_TEST(BPTreeTest, contains)
{
    this->insert(TypeParam::create(11));
    EXPECT_FALSE(this->tree.contains(TypeParam::create_key(12)));
    EXPECT_TRUE(this->const_tree().contains(TypeParam::create_key(11)));
}

TYPED_TEST(BPTreeTest, equal_range)
{
    {
        const auto [from, to] = this->tree.equal_range(TypeParam::create_key(3));
        EXPECT_TRUE(from == to);
    }
    this->insert(TypeParam::create(5));
    {
        auto [from, to] = this->tree.equal_range(TypeParam::create_key(5));
        EXPECT_FALSE(from == to);
        EXPECT_EQ(5, TypeParam::key(*from));
        from->second = TypeParam::create_value(11);
        ++from;
        EXPECT_TRUE(from == to);
    }
    this->insert(TypeParam::create(6));
    this->insert(TypeParam::create(4));
    {
        auto [from, to] = this->const_tree().equal_range(TypeParam::create_key(5));
        EXPECT_FALSE(from == to);
        EXPECT_EQ(5, TypeParam::key(*from));
        EXPECT_TRUE(std::is_const_v<std::remove_reference_t<decltype(*from)>>);
        ++from;
        EXPECT_TRUE(from == to);
    }
}

TYPED_TEST(BPTreeTest, at)
{
    EXPECT_THROW({
                this->tree.at(TypeParam::create_key(7));
            }, std::out_of_range);
    this->insert(TypeParam::create(7));
    const auto key = TypeParam::create_key(7);
    EXPECT_EQ(TypeParam::create_value(7), this->tree.at(key));
    EXPECT_EQ(TypeParam::create_value(7), this->const_tree().at(key));
    EXPECT_TRUE(std::is_lvalue_reference_v<decltype(this->tree.at(key))>) << "'at' method should return an lvalue reference";
    EXPECT_FALSE(std::is_const_v<std::remove_reference_t<decltype(this->tree.at(key))>>) << "non-const 'at' method should return a non-const reference";
    EXPECT_TRUE(std::is_const_v<std::remove_reference_t<decltype(this->const_tree().at(key))>>) << "const 'at' method should return a const reference";
}

TYPED_TEST(BPTreeTest, index)
{
    EXPECT_TRUE(std::is_lvalue_reference_v<decltype(this->tree.operator [](TypeParam::create_key(111)))>) << "operator [] should return an lvalue reference";
    EXPECT_TRUE(TypeParam::empty_value(this->tree[TypeParam::create_key(1)]));
    this->tree[TypeParam::create_key(3)] = TypeParam::create_value(3);
    EXPECT_EQ(TypeParam::create_value(3), this->tree[TypeParam::create_key(3)]);
}

TYPED_TEST(BPTreeTest, insert)
{
    {
        auto key = TypeParam::create_key(33);
        auto value = TypeParam::create_value(33);
        this->tree.insert(key, value);
    }
    {
        const auto key = TypeParam::create_key(51);
        this->tree.insert(key, TypeParam::create_value(51));
    }
    this->tree.insert(TypeParam::create_key(91), TypeParam::create_value(91));
    this->tree.insert({TypeParam::create(1), TypeParam::create(2), TypeParam::create(99)});
    EXPECT_TRUE(this->tree.contains(TypeParam::create_key(1)));
    EXPECT_TRUE(this->tree.contains(TypeParam::create_key(2)));
    EXPECT_TRUE(this->tree.contains(TypeParam::create_key(33)));
    EXPECT_TRUE(this->tree.contains(TypeParam::create_key(51)));
    EXPECT_TRUE(this->tree.contains(TypeParam::create_key(91)));
    EXPECT_TRUE(this->tree.contains(TypeParam::create_key(99)));
    EXPECT_TRUE(this->tree.insert(TypeParam::create_key(13), TypeParam::create_value(13)).second);
    EXPECT_FALSE(this->tree.insert(TypeParam::create_key(13), TypeParam::create_value(13)).second);
}

TYPED_TEST(BPTreeTest, erase_by_iterator)
{
    this->insert(TypeParam::create(11));
    this->insert(TypeParam::create(12));
    this->insert(TypeParam::create(13));
    EXPECT_EQ(3, this->tree.size());
    EXPECT_TRUE(this->tree.contains(TypeParam::create_key(11)));
    EXPECT_TRUE(this->tree.contains(TypeParam::create_key(12)));
    const auto it = this->tree.erase(this->tree.find(TypeParam::create_key(12)));
    EXPECT_FALSE(this->tree.contains(TypeParam::create_key(12)));
    EXPECT_EQ(this->tree.find(TypeParam::create_key(13)), it);
    this->tree.erase(this->const_tree().find(TypeParam::create_key(11)));
    EXPECT_FALSE(this->tree.contains(TypeParam::create_key(11)));
    EXPECT_EQ(1, this->tree.size());
    const auto end_it = this->tree.erase(this->tree.find(TypeParam::create_key(13)));
    EXPECT_EQ(this->tree.end(), end_it);
}

TYPED_TEST(BPTreeTest, erase_range)
{
    for (int i = 19; i < 111; ++i) {
        this->insert(TypeParam::create(i));
    }
    const auto it = this->tree.erase(this->const_tree().find(TypeParam::create_key(51)), this->const_tree().find(TypeParam::create_key(91)));
    const auto expected = this->tree.find(TypeParam::create_key(91));
    EXPECT_EQ(expected, it) << "expected iterator next to [51, 91)";
}

TYPED_TEST(BPTreeTest, erase_key)
{
    this->insert(TypeParam::create(1));
    this->insert(TypeParam::create(3));
    this->insert(TypeParam::create(111));
    EXPECT_EQ(1, this->tree.erase(TypeParam::create_key(3)));
    EXPECT_EQ(0, this->tree.erase(TypeParam::create_key(2)));
}

TYPED_TEST(BPTreeTest, clear)
{
    const int max = 1003;
    for (int i = 0; i < max; ++i) {
        this->insert(TypeParam::create(i));
    }
    EXPECT_EQ(max, this->tree.size());
    EXPECT_TRUE(this->tree.contains(TypeParam::create_key(501)));
    EXPECT_TRUE(this->tree.contains(TypeParam::create_key(1)));
    this->tree.clear();
    EXPECT_TRUE(this->tree.empty());
    EXPECT_FALSE(this->tree.contains(TypeParam::create_key(501)));
    const auto it = this->tree.find(TypeParam::create_key(331));
    EXPECT_EQ(this->tree.end(), it);
}

TYPED_TEST(BPTreeTest, empty)
{
    EXPECT_TRUE(this->tree.empty());
    EXPECT_EQ(0, this->tree.size());
    EXPECT_EQ(this->tree.end(), this->tree.find(TypeParam::create_key(0)));
    EXPECT_EQ(this->tree.end(), this->tree.find(TypeParam::create_key(13)));
    EXPECT_EQ(this->tree.end(), this->tree.find(TypeParam::create_key(101)));
    EXPECT_EQ(this->tree.end(), this->tree.lower_bound(TypeParam::create_key(53)));
    EXPECT_EQ(this->tree.end(), this->tree.upper_bound(TypeParam::create_key(67)));
    std::size_t count = 0;
    for ([[maybe_unused]] const auto & x : this->tree) {
        ++count;
    }
    EXPECT_EQ(0, count);
}

TYPED_TEST(BPTreeTest, singleton)
{
    this->insert(TypeParam::create(17));
    EXPECT_FALSE(this->tree.empty());
    EXPECT_EQ(1, this->tree.size());
    EXPECT_NE(this->tree.end(), this->tree.find(TypeParam::create_key(17)));
    EXPECT_EQ(17, TypeParam::key(*this->tree.find(TypeParam::create_key(17))));
    EXPECT_EQ(1, this->tree.count(TypeParam::create_key(17)));
    EXPECT_EQ(this->tree.find(TypeParam::create_key(17)), this->tree.lower_bound(TypeParam::create_key(17)));
    EXPECT_EQ(this->tree.end(), this->tree.upper_bound(TypeParam::create_key(17)));
    EXPECT_EQ(this->tree.end(), this->tree.find(TypeParam::create_key(7)));
    EXPECT_EQ(this->tree.end(), this->tree.lower_bound(TypeParam::create_key(19)));
    EXPECT_EQ(this->tree.end(), this->tree.upper_bound(TypeParam::create_key(18)));
    std::size_t count = 0;
    for (const auto & x : this->tree) {
        EXPECT_EQ(17, TypeParam::key(x));
        EXPECT_EQ(17, TypeParam::value(x));
        ++count;
    }
    EXPECT_EQ(1, count);
}

TYPED_TEST(BPTreeTest, several)
{
    const int max = 31;
    for (int i = 0; i < max; ++i) {
        this->insert(TypeParam::create(i));
    }
    EXPECT_FALSE(this->tree.empty());
    EXPECT_EQ(max, this->tree.size());
    for (const auto & [key, value] : this->tree) {
        EXPECT_EQ(TypeParam::key(key), TypeParam::value(value));
    }
    for (int i = 0; i < max; ++i) {
        EXPECT_NE(this->tree.end(), this->tree.find(TypeParam::create_key(i))) << "Not found key " << i;
        EXPECT_EQ(1, this->tree.count(TypeParam::create_key(i))) << "Invalid number of entries for key " << i;
        auto it = this->tree.find(TypeParam::create_key(i));
        EXPECT_EQ(i, TypeParam::key(*it)) << "Not found correct key value for " << i;
        EXPECT_EQ(it, this->tree.lower_bound(TypeParam::create_key(i))) << "Not found correct lower bound for key " << i;
        ++it;
        EXPECT_EQ(it, this->tree.upper_bound(TypeParam::create_key(i))) << "Not found correct upper bound for key " << i;
        EXPECT_EQ(i, TypeParam::value(this->tree.at(TypeParam::create_key(i)))) << "Invalid value at " << i;
        EXPECT_EQ(i, TypeParam::value(this->tree[TypeParam::create_key(i)])) << "Invalid value at " << i;
    }
    for (int i = -max; i < 0; ++i) {
        EXPECT_EQ(this->tree.end(), this->tree.find(TypeParam::create_key(i))) << "Found non-existing key " << i;
        EXPECT_EQ(0, this->tree.count(TypeParam::create_key(i))) << "Invalid number of entries for key " << i;
        EXPECT_EQ(this->tree.begin(), this->tree.lower_bound(TypeParam::create_key(i))) << "Not found correct lower bound for key " << i;
        EXPECT_EQ(this->tree.begin(), this->tree.upper_bound(TypeParam::create_key(i))) << "Not found correct upper bound for key " << i;
    }
    for (int i = max; i < 2 * max; ++i) {
        EXPECT_EQ(this->tree.end(), this->tree.find(TypeParam::create_key(i))) << "Found non-existing key " << i;
        EXPECT_EQ(0, this->tree.count(TypeParam::create_key(i))) << "Invalid number of entries for key " << i;
        EXPECT_EQ(this->tree.end(), this->tree.lower_bound(TypeParam::create_key(i))) << "Not found correct lower bound for key " << i;
        EXPECT_EQ(this->tree.end(), this->tree.upper_bound(TypeParam::create_key(i))) << "Not found correct upper bound for key " << i;
    }
}

TYPED_TEST(BPTreeTest, mutating_range_iteration)
{
    const int max = 9;
    for (int i = 0; i < max; ++i) {
        this->insert(TypeParam::create(i));
    }
    for (auto & [key, value] : this->tree) {
        const int v = TypeParam::value(value);
        EXPECT_EQ(TypeParam::key(key), v);
        value = TypeParam::create_value(v * v);
    }
    for (int i = 0; i < max; ++i) {
        const auto it = this->tree.find(TypeParam::create_key(i));
        EXPECT_NE(it, this->tree.end());
        EXPECT_EQ(i, TypeParam::key(*it));
        EXPECT_EQ(i * i, TypeParam::value(*it));
    }
    for (const auto & [key, value] : this->tree) {
        const int k = TypeParam::key(key);
        EXPECT_EQ(k * k, TypeParam::value(value));
    }
}

TYPED_TEST(BPTreeTest, unsorted_insert)
{
    const auto elements = {
        TypeParam::create(111), TypeParam::create(-1), TypeParam::create(0), TypeParam::create(31),
        TypeParam::create(7), TypeParam::create(11), TypeParam::create(17), TypeParam::create(97),
        TypeParam::create(1001), TypeParam::create(-59), TypeParam::create(23)
    };
    this->tree.insert(elements.begin(), elements.end());

    std::vector<typename TypeParam::key_type> sorted_keys;
    sorted_keys.reserve(elements.size());
    for (const auto & x : elements) {
        sorted_keys.emplace_back(x.first);
    }
    std::sort(sorted_keys.begin(), sorted_keys.end());

    EXPECT_EQ(sorted_keys.size(), this->tree.size());
    auto keys_it = sorted_keys.begin();
    for (const auto & [key, value] : this->tree) {
        EXPECT_EQ(*keys_it, key);
        ++keys_it;
    }
}

TYPED_TEST(BPTreeTest, many)
{
    const int max = 11997;
    for (int i = 0; i < max; ++i) {
        this->insert(TypeParam::create(i));
    }
    EXPECT_FALSE(this->tree.empty());
    EXPECT_EQ(max, this->tree.size());
    for (int i = 0; i < max; ++i) {
        EXPECT_NE(this->tree.end(), this->tree.find(TypeParam::create_key(i))) << "Not found key " << i;
        EXPECT_EQ(1, this->tree.count(TypeParam::create_key(i))) << "Invalid number of entries for key " << i;
        EXPECT_EQ(i, TypeParam::key(*this->tree.find(TypeParam::create_key(i)))) << "Not found correct key value for " << i;
        auto it = this->tree.find(TypeParam::create_key(i));
        EXPECT_EQ(it, this->tree.lower_bound(TypeParam::create_key(i))) << "Not found correct lower bound for key " << i;
        ++it;
        EXPECT_EQ(it, this->tree.upper_bound(TypeParam::create_key(i))) << "Not found correct upper bound for key " << i;
        EXPECT_EQ(i, TypeParam::value(this->tree.at(TypeParam::create_key(i)))) << "Invalid value at " << i;
        EXPECT_EQ(i, TypeParam::value(this->tree[TypeParam::create_key(i)])) << "Invalid value at " << i;
    }
    for (const auto & [key, value] : this->tree) {
        EXPECT_EQ(TypeParam::key(key), TypeParam::value(value));
    }
    for (int i = -max; i < 0; ++i) {
        EXPECT_EQ(this->tree.end(), this->tree.find(TypeParam::create_key(i))) << "Found non-existing key " << i;
        EXPECT_EQ(0, this->tree.count(TypeParam::create_key(i))) << "Invalid number of entries for key " << i;
        EXPECT_EQ(this->tree.begin(), this->tree.lower_bound(TypeParam::create_key(i))) << "Not found correct lower bound for key " << i;
        EXPECT_EQ(this->tree.begin(), this->tree.upper_bound(TypeParam::create_key(i))) << "Not found correct upper bound for key " << i;
    }
    for (int i = max; i < 2 * max; ++i) {
        EXPECT_EQ(this->tree.end(), this->tree.find(TypeParam::create_key(i))) << "Found non-existing key " << i;
        EXPECT_EQ(0, this->tree.count(TypeParam::create_key(i))) << "Invalid number of entries for key " << i;
        EXPECT_EQ(this->tree.end(), this->tree.lower_bound(TypeParam::create_key(i))) << "Not found correct lower bound for key " << i;
        EXPECT_EQ(this->tree.end(), this->tree.upper_bound(TypeParam::create_key(i))) << "Not found correct upper bound for key " << i;
    }
}

TYPED_TEST(BPTreeTest, many_unsorted)
{
    const int max = 1001;
    std::vector<int> unsorted(max, 0);
    std::iota(unsorted.begin(), unsorted.end(), 0);
    {
        const auto copy = unsorted;
        unsorted.insert(unsorted.begin(), copy.begin(), copy.end());
        unsorted.insert(unsorted.begin(), copy.begin(), copy.end());
    }
    std::shuffle(unsorted.begin(), unsorted.end(), rgen);
    for (const auto x : unsorted) {
        this->insert(TypeParam::create(x));
    }
    std::vector<int> sorted = unsorted;
    std::sort(sorted.begin(), sorted.end());
    sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());
    EXPECT_EQ(sorted.size(), this->tree.size());
    for (const auto x : sorted) {
        EXPECT_NE(this->tree.end(), this->tree.find(TypeParam::create_key(x)));
        EXPECT_EQ(x, TypeParam::value(*this->tree.find(TypeParam::create_key(x))));
        auto it = this->tree.lower_bound(TypeParam::create_key(x));
        EXPECT_EQ(x, TypeParam::value(*it));
        ++it;
        EXPECT_EQ(it, this->tree.upper_bound(TypeParam::create_key(x)));
    }
    auto expected_it = sorted.begin();
    for (const auto & [key, value] : this->tree) {
        EXPECT_EQ(*expected_it, TypeParam::key(key));
        EXPECT_EQ(*expected_it, TypeParam::value(value));
        ++expected_it;
    }
}

using TypesToTest = ::testing::Types<BPTreeTest<Type<std::string, std::string>>>;
INSTANTIATE_TYPED_TEST_SUITE_P(BPTree, IteratorTest, TypesToTest);
