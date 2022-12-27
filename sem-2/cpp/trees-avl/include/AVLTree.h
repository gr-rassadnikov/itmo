#pragma once

#include <vector>

class Node
{
public:
    Node * left;
    Node * right;
    const int value;
    int height;
    int size;
    Node(int value);
    ~Node();
};

class AVLTree
{
private:
    Node * root = nullptr;

    static int _height(Node * node);
    static void _change_height(Node * node);
    static int _size(Node * node);
    static void _change_size(Node * node);
    static Node * _right_rotate(Node * right);
    static Node * _left_rotate(Node * left);
    static int _get_balance(Node * node);
    static Node * _change_balance(Node * node);
    static Node * _insert(Node * node, int value, bool & result);
    static bool _contains(Node * node, int value);
    static Node * _find_min(Node * node);
    static Node * _remove_min(Node * node);
    static Node * _remove(Node * node, int value, bool & result);
    static void _values(Node * node, std::vector<int> & data_values);

public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);
    std::size_t size() const;
    bool empty() const;
    std::vector<int> values() const;
    ~AVLTree();
};
