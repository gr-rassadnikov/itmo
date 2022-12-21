#pragma once
#include <array>
#include <iostream>

namespace tree_details {

template <class T>
constexpr bool IsConst = false;
template <template <bool> class T>
constexpr bool IsConst<T<true>> = true;

} // namespace tree_details

template <class Key, class Value, std::size_t BlockSize = 4096, class Less = std::less<Key>>
class BPTree
{
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<Key, Value>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using size_type = std::size_t;

private:
    class Node;
    class Leaf;
    class Internal;

    static constexpr size_type size_of_block = ((BlockSize - sizeof(void *)) / (sizeof(key_type) + sizeof(void *)));
    size_type tree_size = 0;
    Node * root = nullptr;
    static constexpr Less less_keys{};

    class Node
    {
        friend class BPTree;

    protected:
        Internal * parent = nullptr;
        size_type keys_number = 0;

        Node() = default;
        Node(Internal * parent, size_type keys_number);
        Internal * getParent() const;
        size_type getKeysNumber() const;
        virtual ~Node() = default;

        virtual bool is_leaf() const = 0;
        virtual size_type lower_bound(const Key & key) = 0;
        virtual Leaf * find_leaf(const Key & key) = 0;
        virtual size_type cut() = 0;
        virtual Leaf * get_begin_leaf() = 0;
        virtual Leaf * get_end_leaf() = 0;
        virtual Internal * getInternal() = 0;
        virtual Leaf * getLeaf() = 0;
    };

    class Leaf : public Node
    {
        friend class BPTree;

    private:
        Leaf * next_leaf = nullptr;
        std::array<value_type, size_of_block + 1> data;

        Leaf() = default;
        Leaf(size_type keys_number,
             Node * parent,
             Leaf * next_leaf,
             std::array<mapped_type, size_of_block + 1> data);
        ~Leaf() = default;

        bool is_leaf() const override;
        size_type lower_bound(const Key & key) override;
        size_type cut() override;
        Leaf * get_begin_leaf() override;
        Leaf * get_end_leaf() override;
        Internal * getInternal() override;
        Leaf * getLeaf() override;

        template <class K, class V>
        size_type insert(K && key, V && value);

        size_type upper_bound(const Key & key);
        bool contains(const Key & key);
        Leaf * find_leaf(const Key &) override;
        Leaf * split(size_type & index, bool & index_send);
        value_type & get_data(size_type index);
        size_type erase_index(size_type index);
        void merge(Leaf * right);
        Leaf * get_left_brother();
    };

    class Internal : public Node
    {
        friend class BPTree;

    private:
        std::array<key_type, size_of_block> keys;
        std::array<Node *, size_of_block + 1> child;

        Internal() = default;
        Internal(size_type keys_number,
                 Internal * parent,
                 std::array<key_type, size_of_block> keys,
                 std::array<Node *, size_of_block + 1> child);
        ~Internal();

        bool is_leaf() const override;
        size_type lower_bound(const Key & key) override;
        Leaf * find_leaf(const Key & key) override;
        size_type cut() override;
        Leaf * get_begin_leaf() override;
        Leaf * get_end_leaf() override;
        Internal * getInternal() override;
        Leaf * getLeaf() override;

        void insert(Node * children, const Key & key);
        Internal * split(Key & get_key_after_split);
        void erase_unnecessary_child();
        void merge(Internal * right, Key & key_to_back);
        void change_key(Key & from, Key & to);
        Internal * get_left_brother();
        Internal * get_right_brother();
        Key & get_key_between_l_r(Internal * left, Internal * right);
        Key & get_key_between_l_r_leaf(Leaf * left, Leaf * right);
        Key & compare_child_between_l_r_and_get_key(Internal * left, Internal * right, Key & key_between_l_r);
    };

public:
    BPTree() = default;
    BPTree(std::initializer_list<std::pair<key_type, mapped_type>> list);
    BPTree(const BPTree & other);
    BPTree(BPTree && other);
    BPTree & operator=(BPTree & other);
    BPTree & operator=(BPTree && other);
    ~BPTree();

    bool empty() const;
    bool contains(const Key & key) const;
    size_type count(const Key & key) const;
    size_type size() const;
    void clear();

    template <bool is_const>
    class Iterator;

    using iterator = Iterator<false>;
    using const_iterator = Iterator<true>;

    std::pair<iterator, bool> insert(const Key & key, const Value & value)
    {
        return insertImpl(key, value);
    }
    std::pair<iterator, bool> insert(const Key & key, Value && value)
    {
        return insertImpl(key, std::move(value));
    }

    template <class ForwardIt>
    void insert(ForwardIt begin, ForwardIt end);

    void insert(std::initializer_list<value_type> list);

    iterator begin();
    const_iterator cbegin() const;
    const_iterator begin() const;
    iterator end();
    const_iterator cend() const;
    const_iterator end() const;

    iterator find(const Key & key);
    const_iterator find(const Key & key) const;
    Value & at(const Key & key);
    const Value & at(const Key & key) const;

    iterator lower_bound(const Key & key);
    const_iterator lower_bound(const Key & key) const;
    iterator upper_bound(const Key & key);
    const_iterator upper_bound(const Key & key) const;
    std::pair<iterator, iterator> equal_range(const Key & key);
    std::pair<const_iterator, const_iterator> equal_range(const Key & key) const;

    Value & operator[](const Key & key);

    iterator erase(const_iterator it);
    iterator erase(const_iterator begin, const_iterator end);
    size_type erase(const Key &);

private:
    template <class K, class V>
    std::pair<iterator, bool> insertImpl(K && key, V && value);
};

template <class Key, class Value, std::size_t BlockSize, class Less>
BPTree<Key, Value, BlockSize, Less>::Node::Node(Internal * parent, size_type keys_number)
    : parent(parent)
    , keys_number(keys_number)
{
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Node::getParent() const -> Internal *
{
    return parent;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Node::getKeysNumber() const -> size_type
{
    return keys_number;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
BPTree<Key, Value, BlockSize, Less>::Leaf::Leaf(size_type keys_number, Node * parent, Leaf * next_leaf, std::array<mapped_type, size_of_block + 1> data)
    : Node(parent, keys_number)
    , next_leaf(next_leaf)
    , data(data)
{
}

template <class Key, class Value, std::size_t BlockSize, class Less>
bool BPTree<Key, Value, BlockSize, Less>::Leaf::is_leaf() const
{
    return true;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Leaf::lower_bound(const Key & key) -> size_type
{
    size_type i = 0;
    while (i < this->getKeysNumber() && less_keys(data[i].first, key)) {
        i++;
    }
    return i;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Leaf::cut() -> size_type
{
    return this->keys_number / 2;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
template <class K, class V>
auto BPTree<Key, Value, BlockSize, Less>::Leaf::insert(K && key, V && value) -> size_type
{
    size_type index = lower_bound(key);
    for (size_type i = this->keys_number; i > index; i--) {
        data[i] = {std::forward<K>(data[i - 1].first), std::forward<V>(data[i - 1].second)};
    }
    data[index] = {std::forward<K>(key), std::forward<V>(value)};
    this->keys_number++;
    return index;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Leaf::get_begin_leaf() -> Leaf *
{
    return this;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Leaf::get_end_leaf() -> Leaf *
{
    return this;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Leaf::getInternal() -> Internal *
{
    return nullptr;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Leaf::getLeaf() -> Leaf *
{
    return this;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Leaf::upper_bound(const Key & key) -> size_type
{
    size_type i = 0;
    while (i < this->getKeysNumber() && !less_keys(key, data[i].first)) {
        i++;
    }
    return i;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
bool BPTree<Key, Value, BlockSize, Less>::Leaf::contains(const Key & key)
{
    size_type i = 0;
    while (i < this->getKeysNumber() && less_keys(data[i].first, key)) {
        i++;
    }
    return !less_keys(data[i].first, key) && !less_keys(key, data[i].first);
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Leaf::find_leaf(const Key &) -> Leaf *
{
    return this;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Leaf::split(size_type & index, bool & index_send) -> Leaf *
{
    size_type size_left = cut();
    size_type size_right = this->keys_number - size_left;
    this->keys_number = size_left;
    if (index >= this->keys_number) {
        index -= this->keys_number;
        index_send = true;
    }
    size_type ind = 0;
    Leaf * right_leaf = new Leaf;
    right_leaf->next_leaf = next_leaf;
    next_leaf = right_leaf;
    while (ind < size_right) {
        right_leaf->data[ind] = std::move(data[ind + size_left]);
        ind++;
    }
    right_leaf->parent = this->parent;
    right_leaf->keys_number = size_right;
    return right_leaf;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Leaf::get_data(size_type index) -> value_type &
{
    return data[index];
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Leaf::erase_index(size_type index) -> size_type
{
    if (this->keys_number == 0) {
        this->keys_number = 1;
    }
    for (size_type i = index; i < this->keys_number - 1; i++) {
        data[i] = std::move(data[i + 1]);
    }
    this->keys_number--;

    return index;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
void BPTree<Key, Value, BlockSize, Less>::Leaf::merge(Leaf * right)
{
    for (size_type i = 0; i < right->keys_number; i++) {
        data[this->keys_number] = right->data[i];
        this->keys_number++;
    }
    right->parent = nullptr;
    next_leaf = right->next_leaf;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Leaf::get_left_brother() -> Leaf *
{
    if (this->parent == nullptr) {
        return nullptr;
    }
    Leaf * last = nullptr;
    for (size_type i = 0; i <= this->parent->getKeysNumber(); i++) {
        if (this->parent->child[i] == this) {
            return last;
        }
        last = this->parent->child[i]->getLeaf();
    }
    return nullptr;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
BPTree<Key, Value, BlockSize, Less>::Internal::Internal(size_type keys_number, Internal * parent, std::array<key_type, size_of_block> keys, std::array<Node *, size_of_block + 1> child)
    : Node(parent, keys_number)
    , keys(keys)
    , child(child)
{
}

template <class Key, class Value, std::size_t BlockSize, class Less>
BPTree<Key, Value, BlockSize, Less>::Internal::~Internal()
{
    for (size_type i = 0; i <= this->keys_number; i++) {
        delete child[i];
    }
}
template <class Key, class Value, std::size_t BlockSize, class Less>
bool BPTree<Key, Value, BlockSize, Less>::Internal::is_leaf() const
{
    return false;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Internal::lower_bound(const Key & key) -> size_type
{
    size_type i = 0;
    while (i < this->keys_number && !less_keys(key, keys[i])) {
        i++;
    }
    return i;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Internal::find_leaf(const Key & key) -> Leaf *
{
    size_type index = lower_bound(key);
    return child[index]->find_leaf(key);
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Internal::cut() -> size_type
{
    return (this->keys_number + 1) / 2;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Internal::get_begin_leaf() -> Leaf *
{
    if (child[0] == nullptr) {
        return nullptr;
    }
    return child[0]->get_begin_leaf();
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Internal::get_end_leaf() -> Leaf *
{
    if (child[this->keys_number] == nullptr) {
        return nullptr;
    }
    return child[this->keys_number]->get_end_leaf();
}

template <class Key, class Value, std::size_t BlockSize, class Less>
void BPTree<Key, Value, BlockSize, Less>::Internal::insert(Node * children, const Key & key)
{
    size_type index = lower_bound(key);
    for (size_type i = this->keys_number; i > index; i--) {
        keys[i] = keys[i - 1];
    }
    keys[index] = key;

    for (size_type i = this->keys_number + 1; i > index + 1; i--) {
        child[i] = child[i - 1];
    }
    children->parent = this;
    child[index + 1] = children;
    this->keys_number++;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Internal::split(Key & get_key_after_split) -> Internal *
{
    size_type size_left = cut();
    size_type size_right = this->keys_number - size_left;
    this->keys_number = size_left - 1;
    get_key_after_split = keys[this->keys_number];
    size_type ind = 0;
    Internal * right_internal = new Internal();
    while (ind < size_right) {
        right_internal->keys[ind] = keys[ind + size_left];
        right_internal->child[ind] = child[ind + size_left];
        right_internal->child[ind]->parent = right_internal;
        ind++;
    }
    right_internal->child[size_right] = child[size_right + size_left];
    right_internal->child[size_right]->parent = right_internal;
    right_internal->parent = this->parent;
    right_internal->keys_number = size_right;
    return right_internal;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
void BPTree<Key, Value, BlockSize, Less>::Internal::erase_unnecessary_child()
{
    size_type index_delete_key = 0;
    for (size_type i = 0; i <= this->keys_number; i++) {
        if (child[i]->parent == nullptr) {
            if (i > 0) {
                index_delete_key = i - 1;
            }
            delete child[i];
            for (size_type j = i; j < this->keys_number; j++) {
                child[j] = child[j + 1];
            }
            child[this->keys_number] = nullptr;
            break;
        }
    }
    if (this->keys_number > 0) {
        for (size_type i = index_delete_key; i < this->keys_number - 1; i++) {
            keys[i] = keys[i + 1];
        }
        this->keys_number--;
    }
}

template <class Key, class Value, std::size_t BlockSize, class Less>
void BPTree<Key, Value, BlockSize, Less>::Internal::merge(Internal * right, Key & key_to_back)
{
    keys[this->keys_number] = key_to_back;
    this->keys_number++;
    for (size_type i = 0; i < right->keys_number; i++) {
        keys[this->keys_number] = right->keys[i];
        child[this->keys_number] = right->child[i];
        this->keys_number++;
    }
    child[this->keys_number] = right->child[right->keys_number];
    for (size_type i = 0; i <= this->keys_number; i++) {
        child[i]->parent = this;
    }
    right->parent = nullptr;
    for (size_type i = 0; i <= size_of_block; i++) {
        right->child[i] = nullptr;
    }
}

template <class Key, class Value, std::size_t BlockSize, class Less>
void BPTree<Key, Value, BlockSize, Less>::Internal::change_key(Key & from, Key & to)
{
    for (size_type i = 0; i < this->keys_number; i++) {
        if (!less_keys(keys[i], from) && !less_keys(from, keys[i])) {
            keys[i] = to;
            break;
        }
    }
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Internal::get_left_brother() -> Internal *
{
    if (this->parent == nullptr) {
        return nullptr;
    }
    Internal * last = nullptr;
    for (size_type i = 0; i <= this->parent->keys_number; i++) {
        if (this->parent->child[i] == this) {
            return last;
        }
        last = this->parent->child[i]->getInternal();
    }
    return nullptr;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Internal::get_right_brother() -> Internal *
{
    if (this->parent == nullptr) {
        return nullptr;
    }
    Internal * last = nullptr;
    for (size_type i = this->parent->keys_number;; i--) {
        if (this->parent->child[i] == this) {
            return last;
        }
        last = this->parent->child[i]->getInternal();
        if (i == 0) {
            break;
        }
    }
    return nullptr;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Internal::get_key_between_l_r(Internal * left, Internal * right) -> Key &
{
    for (size_type i = 0; i < this->keys_number; i++) {
        if (child[i] == left && child[i + 1] == right) {
            return keys[i];
        }
    }
    return keys[0];
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Internal::get_key_between_l_r_leaf(Leaf * left, Leaf * right) -> Key &
{
    for (size_type i = 0; i < this->keys_number; i++) {
        if (child[i] == left && child[i + 1] == right) {
            return keys[i];
        }
    }
    return keys[0];
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Internal::compare_child_between_l_r_and_get_key(Internal * left, Internal * right, Key & key_between_l_r) -> Key &
{
    const size_type cnt_keys = left->keys_number + right->keys_number + 1;
    const size_type left_size = cnt_keys / 2;
    const size_type right_size = cnt_keys - left_size - 1;
    if (left->keys_number < left_size) {
        left->keys[left->keys_number] = key_between_l_r;
        left->keys_number++;
        size_type index = 0;
        while (left->keys_number < left_size) {
            left->keys[left->keys_number] = right->keys[index];
            left->child[left->keys_number] = right->child[index];
            left->keys_number++;
            index++;
        }
        left->child[left->keys_number] = right->child[index];
        right->keys[size_of_block - 1] = right->keys[index];
        for (size_type i = 0; i < right_size - 1; i++) {
            right->keys[i] = right->keys[i + index + 1];
            right->child[i] = right->child[i + index + 1];
        }
        right->child[right_size] = right->child[right->keys_number];
        right->keys_number = right_size;
        return right->keys[size_of_block - 1];
    }
    if (left->keys_number > left_size) {
        size_type index = right_size - 1;
        for (size_type i = right->keys_number; i > 0; i--) {
            right->keys[index] = right->keys[i - 1];
            right->child[index + 1] = right->child[i];
            index--;
        }
        right->keys[index] = key_between_l_r;
        right->child[index + 1] = right->child[0];
        while (index > 0) {
            right->keys[index - 1] = left->keys[left->keys_number - 1];
            right->child[index] = left->child[left->keys_number];
            index--;
            left->keys_number--;
        }
        right->child[0] = left->child[left->keys_number];
        left->keys_number = left_size;
        right->keys_number = right_size;
        return left->keys[left_size];
    }
    return key_between_l_r;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Internal::getInternal() -> Internal *
{
    return this;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::Internal::getLeaf() -> Leaf *
{
    return nullptr;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
BPTree<Key, Value, BlockSize, Less>::BPTree(std::initializer_list<std::pair<key_type, mapped_type>> list)
{
    for (auto it : list) {
        insert(it.first, it.second);
    }
}

template <class Key, class Value, std::size_t BlockSize, class Less>
BPTree<Key, Value, BlockSize, Less>::BPTree(const BPTree & other)
{
    for (const_iterator it = other.cbegin(); it != other.cend(); it++) {
        insert(it->first, it->second);
    }
}

template <class Key, class Value, std::size_t BlockSize, class Less>
BPTree<Key, Value, BlockSize, Less>::BPTree(BPTree && other)
    : tree_size(other.tree_size)
{
    std::swap(root, other.root);
    other.tree_size = 0;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::operator=(BPTree & other) -> BPTree &
{
    auto copy = other;
    std::swap(root, copy.root);
    std::swap(tree_size, copy.tree_size);
    return *this;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::operator=(BPTree && other) -> BPTree &
{
    std::swap(root, other.root);
    std::swap(tree_size, other.tree_size);
    return *this;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
BPTree<Key, Value, BlockSize, Less>::~BPTree()
{
    delete root;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
bool BPTree<Key, Value, BlockSize, Less>::empty() const
{
    return root == nullptr;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
bool BPTree<Key, Value, BlockSize, Less>::contains(const Key & key) const
{
    if (root == nullptr) {
        return false;
    }
    Leaf * leaf = root->find_leaf(key);
    for (size_type i = 0; i < leaf->getKeysNumber(); i++) {
        if (!less_keys(key, leaf->data[i].first) && !less_keys(leaf->data[i].first, key)) {
            return true;
        }
    }
    return false;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::count(const Key & key) const -> size_type
{
    return contains(key) ? 1 : 0;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::size() const -> size_type
{
    return tree_size;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
void BPTree<Key, Value, BlockSize, Less>::clear()
{
    delete root;
    root = nullptr;
    tree_size = 0;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
template <class K, class V>
auto BPTree<Key, Value, BlockSize, Less>::insertImpl(K && key, V && value) -> std::pair<iterator, bool>
{
    if (find(key) != end()) {
        return {find(key), false};
    }
    tree_size++;
    if (root == nullptr) {
        Leaf * leaf = new Leaf;
        leaf->insert(std::forward<K>(key), std::forward<V>(value));
        root = leaf;
        return {iterator(*this, leaf), true};
    }
    Leaf * leaf = root->find_leaf(key);
    bool was_key = leaf->contains(key);
    size_type index = leaf->insert(std::forward<K>(key), std::forward<V>(value));
    if (leaf->getKeysNumber() == size_of_block + 1) {
        bool index_send = false;
        Leaf * new_right_leaf = leaf->split(index, index_send);
        Internal * parent;
        if (leaf->parent == nullptr) {
            leaf->parent = new Internal;
            leaf->parent->child[0] = leaf;
        }
        parent = leaf->parent;
        parent->insert(new_right_leaf, new_right_leaf->data[0].first);
        while (parent->getKeysNumber() == size_of_block) {
            Key get_key_after_split;
            Internal * new_right_internal = parent->split(get_key_after_split);
            if (parent->parent == nullptr) {
                parent->parent = new Internal;
                parent->parent->child[0] = parent;
            }
            parent->parent->insert(new_right_internal, get_key_after_split);
            parent = parent->parent;
        }
        if (parent->parent == nullptr) {
            root = parent;
        }
        return {iterator(*this, !index_send ? leaf : new_right_leaf, index), !was_key};
    }
    return {iterator(*this, leaf, index), !was_key};
}

template <class Key, class Value, std::size_t BlockSize, class Less>
template <class ForwardIt>
void BPTree<Key, Value, BlockSize, Less>::insert(ForwardIt begin, ForwardIt end)
{
    for (auto it = begin; it < end; it++) {
        insert(it->first, it->second);
    }
}

template <class Key, class Value, std::size_t BlockSize, class Less>
void BPTree<Key, Value, BlockSize, Less>::insert(std::initializer_list<value_type> list)
{
    for (auto it : list) {
        insert(it.first, it.second);
    }
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::begin() -> iterator
{
    return iterator(*this, root ? root->get_begin_leaf() : nullptr);
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::cbegin() const -> const_iterator
{
    return const_iterator(*this, root ? root->get_begin_leaf() : nullptr);
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::begin() const -> const_iterator
{
    return const_iterator(*this, root ? root->get_begin_leaf() : nullptr);
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::end() -> iterator
{
    return iterator(*this);
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::cend() const -> const_iterator
{
    return const_iterator(*this);
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::end() const -> const_iterator
{
    return const_iterator(*this);
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::find(const Key & key) -> iterator
{
    if (root == nullptr) {
        return iterator(*this);
    }
    Leaf * leaf = root->find_leaf(key);
    size_type index = leaf->lower_bound(key);
    if (less_keys(leaf->data[index].first, key) || less_keys(key, leaf->data[index].first)) {
        return end();
    }
    return iterator(*this, leaf, index);
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::find(const Key & key) const -> const_iterator
{
    if (root == nullptr) {
        return const_iterator(*this);
    }
    Leaf * leaf = root->find_leaf(key);
    size_type index = leaf->lower_bound(key);
    if (less_keys(leaf->data[index].first, key) || less_keys(key, leaf->data[index].first)) {
        return cend();
    }
    return const_iterator(*this, leaf, index);
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::at(const Key & key) -> Value &
{
    //    return (const_cast<const BPTree<Key, Value, BlockSize, Less> >(*this)).at(key);
    if (root == nullptr) {
        throw std::out_of_range("Tree is empty");
    }
    Leaf * leaf = root->find_leaf(key);
    size_type index = leaf->lower_bound(key);
    return leaf->data[index].second;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::at(const Key & key) const -> const Value &
{
    if (root == nullptr) {
        throw std::out_of_range("Tree is empty");
    }
    Leaf * leaf = root->find_leaf(key);
    size_type index = leaf->lower_bound(key);
    return leaf->data[index].second;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::lower_bound(const Key & key) -> iterator
{
    if (root == nullptr) {
        return iterator(*this);
    }
    Leaf * leaf = root->find_leaf(key);
    size_type index = leaf->lower_bound(key);
    if (less_keys(leaf->data[index].first, key)) {
        return end();
    }
    return iterator(*this, leaf, index);
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::lower_bound(const Key & key) const -> const_iterator
{
    if (root == nullptr) {
        return const_iterator(*this);
    }
    Leaf * leaf = root->find_leaf(key);
    size_type index = leaf->lower_bound(key);
    if (less_keys(leaf->data[index].first, key)) {
        return end();
    }
    return const_iterator(*this, leaf, index);
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::upper_bound(const Key & key) -> iterator
{
    if (!root) {
        return iterator(*this);
    }
    Leaf * leaf = root->find_leaf(key);
    size_type index = leaf->upper_bound(key);
    while (leaf && index == leaf->getKeysNumber()) {
        leaf = leaf->next_leaf;
        index = leaf ? leaf->upper_bound(key) : 0;
    }
    return iterator(*this, leaf, index);
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::upper_bound(const Key & key) const -> const_iterator
{
    if (!root) {
        return const_iterator(*this);
    }
    Leaf * leaf = root->find_leaf(key);
    size_type index = leaf->upper_bound(key);
    while (leaf && index == leaf->getKeysNumber()) {
        leaf = leaf->next_leaf;
        index = leaf ? leaf->upper_bound(key) : 0;
    }
    return const_iterator(*this, leaf, index);
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::equal_range(const Key & key) -> std::pair<iterator, iterator>
{
    return {lower_bound(key), upper_bound(key)};
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::equal_range(const Key & key) const -> std::pair<const_iterator, const_iterator>
{
    return {lower_bound(key), upper_bound(key)};
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::operator[](const Key & key) -> Value &
{
    iterator it = find(key);
    if (it == end()) {
        auto [it_insert, b] = insert(key, Value());
        return it_insert->second;
    }
    return it->second;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::erase(const_iterator it) -> iterator
{
    size_type index = it.index;
    Key key_end = it.leaf->data[index].first;
    Leaf * leaf = it.leaf;
    leaf->erase_index(index);
    tree_size--;
    if (leaf->parent != nullptr && leaf->getKeysNumber() < (size_of_block + 1) / 2) {
        Leaf * right_ne = leaf->next_leaf;
        Internal * internal = leaf->parent;
        bool change_child = false;
        Leaf * right_leaf;
        Leaf * left_leaf;
        if (right_ne != nullptr && right_ne->parent == leaf->parent) {
            left_leaf = leaf;
            right_leaf = right_ne;
        }
        else {
            left_leaf = leaf->get_left_brother();
            right_leaf = leaf;
        }

        if (left_leaf->getKeysNumber() + right_leaf->getKeysNumber() <= size_of_block) {
            left_leaf->merge(right_leaf);
            change_child = true;
        }
        else {
            if (leaf == left_leaf) {
                value_type vl = right_leaf->get_data(0);
                left_leaf->insert(vl.first, std::move(vl.second));
                right_leaf->erase_index(0);
            }
            else {
                value_type vl = left_leaf->get_data(left_leaf->getKeysNumber() - 1);
                right_leaf->insert(vl.first, std::move(vl.second));
                left_leaf->erase_index(left_leaf->getKeysNumber());
            }
            Key & key_change = internal->get_key_between_l_r_leaf(left_leaf, right_leaf);
            internal->change_key(key_change, right_leaf->data[0].first);
        }

        while (change_child && internal != nullptr) {
            internal->erase_unnecessary_child();
            if (internal->parent == nullptr) {
                break;
            }
            change_child = false;
            if (internal->getKeysNumber() < (size_of_block) / 2) {
                Internal * left_brother = internal->get_left_brother();
                Internal * right_brother;
                Internal * left;
                Internal * right;
                if (left_brother == nullptr) {
                    right_brother = internal->get_right_brother();
                    left = internal;
                    right = right_brother;
                }
                else {
                    left = left_brother;
                    right = internal;
                }
                Internal * parent = left->parent;
                Key & key_between_l_r = parent->get_key_between_l_r(left, right);
                if (left->getKeysNumber() + right->getKeysNumber() + 1 >= size_of_block) {
                    Key & new_key_for_parent = parent->compare_child_between_l_r_and_get_key(left, right, key_between_l_r);
                    parent->change_key(key_between_l_r, new_key_for_parent);
                }
                else {
                    left->merge(right, key_between_l_r);
                    change_child = true;
                }
                internal = parent;
            }
        }
        if (root == internal && internal->getKeysNumber() == 0) {
            root = internal->child[0];
            for (size_type i = 0; i <= size_of_block; i++) {
                internal->child[i] = nullptr;
            }
            delete internal;
            root->parent = nullptr;
        }
    }
    return upper_bound(key_end);
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::erase(const_iterator begin, const_iterator end) -> iterator
{
    Key key_end = end.leaf->data[end.index].first;
    iterator it = iterator(*this, begin.leaf, begin.index);
    while (less_keys(it.leaf->get_data(it.index).first, key_end)) {
        it = erase(it);
    }
    return it;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
auto BPTree<Key, Value, BlockSize, Less>::erase(const Key & key) -> size_type
{
    const_iterator c_it = find(key);
    if (c_it == cend()) {
        return 0;
    }
    erase(c_it);
    return 1;
}

template <class Key, class Value, std::size_t BlockSize, class Less>
template <bool is_const>
class BPTree<Key, Value, BlockSize, Less>::Iterator
{
    friend class BPTree;

public:
    using difference_type = std::ptrdiff_t;
    using value_type = std::conditional_t<is_const, const value_type, value_type>;
    using pointer = value_type *;
    using reference = value_type &;
    using iterator_category = std::forward_iterator_tag;

    Iterator() = default;

    template <class R = Iterator, std::enable_if_t<tree_details::IsConst<R>, int> = 0>
    Iterator(const Iterator<false> & other)
        : tree(other.tree)
        , leaf(other.leaf)
        , index(other.index)
    {
    }

    reference operator*() const
    {
        return leaf->get_data(index);
    }

    pointer operator->() const
    {
        return &(leaf->get_data(index));
    }

    friend bool operator==(const Iterator & lhs, const Iterator & rhs)
    {
        return lhs.index == rhs.index && lhs.leaf == rhs.leaf && lhs.tree == rhs.tree;
    }
    friend bool operator!=(const Iterator & lhs, const Iterator & rhs)
    {
        return !(lhs == rhs);
    }

    Iterator & operator++()
    {
        if (index + 1 == leaf->getKeysNumber()) {
            leaf = leaf->next_leaf;
            index = 0;
        }
        else {
            index++;
        }
        return *this;
    }

    Iterator operator++(int)
    {
        auto tmp = *this;
        operator++();
        return tmp;
    }

private:
    Iterator(const BPTree & tree, Leaf * node = nullptr, std::size_t index = 0)
        : tree(&tree)
        , leaf(node)
        , index(index)

    {
    }

    const BPTree * tree = nullptr;
    Leaf * leaf = nullptr;
    std::size_t index = 0;
};
