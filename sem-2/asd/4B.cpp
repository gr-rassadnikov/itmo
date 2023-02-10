#include <vector>
#include <algorithm>
#include <string>
#include <deque>
#include <map>
#include <set>
#include <cmath>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <random>

using namespace std;

class Node {
public:
    Node *left;
    Node *right;
    const int value;
    int key;
    int size;
    int height;

    Node(int value) :
            value(value) {
//        std::random_device x;
//        std::mt19937 get(x());
        key = rand() + rand() * rand() + rand() * rand();
        size = 1;
        left = nullptr;
        right = nullptr;
    }
};

class AVLTree {
private:
    Node *root = nullptr;

    static int _height(Node *node);

    static void _change_height(Node *node);

    static int _size(Node *node);

    static void _change_size(Node *node);

    static Node *_right_rotate(Node *right);

    static Node *_left_rotate(Node *left);

    static int _get_balance(Node *node);

    static Node *_change_balance(Node *node);

    static Node *_insert(Node *node, int value, bool &result);

    static bool _contains(Node *node, int value);

    static Node *_find_min(Node *node);

    static Node *_remove_min(Node *node);

    static Node *_remove(Node *node, int value, bool &result);

    static void _values(Node *node, std::vector<int> &data_values);

public:
    bool contains(int value) const;

    bool insert(int value);

    bool remove(int value);

    std::size_t size() const;

    bool empty() const;

    std::vector<int> values() const;

    int get_k(int k);

    ~AVLTree();
};


int AVLTree::_height(Node *node) {
    return node == nullptr ? 0 : node->height;
}

void AVLTree::_change_height(Node *node) {
    node->height = std::max(_height(node->left), _height(node->right)) + 1;
}

int AVLTree::_size(Node *node) {
    return node == nullptr ? 0 : node->size;
}

void AVLTree::_change_size(Node *node) {
    if (node == nullptr) {
        return;
    }
    node->size = _size(node->left) + _size(node->right) + 1;
}

Node *AVLTree::_right_rotate(Node *right) {
    Node *left = right->left;
    right->left = left->right;
    left->right = right;
    _change_height(left);
    _change_height(right);
    if (left != nullptr) {
        _change_size(left->left);
        _change_size(left->right);
    }
    if (right != nullptr) {
        _change_size(right->left);
        _change_size(right->right);
    }
    _change_size(left);
    _change_size(right);
    return left;
}

Node *AVLTree::_left_rotate(Node *left) {
    Node *right = left->right;
    left->right = right->left;
    right->left = left;
    _change_height(left);
    _change_height(right);
    if (left != nullptr) {
        _change_size(left->left);
        _change_size(left->right);
    }
    if (right != nullptr) {
        _change_size(right->left);
        _change_size(right->right);
    }
    _change_size(left);
    _change_size(right);
    return right;
}

int AVLTree::_get_balance(Node *node) {
    return node == nullptr ? 0 : _height(node->right) - _height(node->left);
}

Node *AVLTree::_change_balance(Node *node) {
    _change_height(node);
    _change_size(node);
    if (_get_balance(node) == -2) {
        if (_get_balance(node->left) > 0) {
            node->left = _left_rotate(node->left);
        }
        return _right_rotate(node);
    } else if (_get_balance(node) == 2) {
        if (_get_balance(node->right) < 0) {
            node->right = _right_rotate(node->right);
        }
        return _left_rotate(node);
    }
    return node;
}

Node *AVLTree::_insert(Node *node, int value, bool &result) {
    if (node == nullptr)
        return new Node(value);

    if (node->value == value) {
        result = false;
    } else if (node->value > value) {
        node->left = _insert(node->left, value, result);
        _change_size(node->left);
        _change_size(node->right);
        _change_size(node);
    } else {
        node->right = _insert(node->right, value, result);
        _change_size(node->left);
        _change_size(node->right);
        _change_size(node);
    }
    return _change_balance(node);
}

bool AVLTree::_contains(Node *node, int value) {
    if (node == nullptr) {
        return false;
    }
    if (node->value == value) {
        return true;
    }
    if (value < node->value) {
        return _contains(node->left, value);
    } else {
        return _contains(node->right, value);
    }
}

Node *AVLTree::_find_min(Node *node) {
    return node->left == nullptr ? node : _find_min(node->left);
}

Node *AVLTree::_remove_min(Node *node) {
    if (node->left == nullptr)
        return node->right;
    node->left = _remove_min(node->left);
    _change_size(node->left);
    _change_size(node->right);
    _change_size(node);
    return _change_balance(node);
}

Node *AVLTree::_remove(Node *node, int value, bool &result) {
    if (node == nullptr)
        return nullptr;
    if (node->value == value) {
        result = true;
        Node *right_child = node->right;
        Node *left_child = node->left;
        _change_size(node->left);
        _change_size(node->right);
        _change_size(node);
        node->left = nullptr;
        node->right = nullptr;
        _change_size(node);
        _change_size(right_child);
        _change_size(left_child);
        delete node;
        if (right_child == nullptr) {
            return left_child;
        }
        Node *new_node = _find_min(right_child);

        _change_size(right_child);
        _change_size(left_child);
        new_node->right = _remove_min(right_child);
        new_node->left = left_child;
        _change_size(right_child);
        _change_size(left_child);
        _change_size(new_node);
        _change_size(new_node->right);
        _change_size(new_node->left);
        _change_size(right_child);
        _change_size(left_child);

        return _change_balance(new_node);
    } else if (value < node->value) {
        node->left = _remove(node->left, value, result);
        _change_size(node->left);
        _change_size(node->right);
        _change_size(node);
    } else {
        node->right = _remove(node->right, value, result);
        _change_size(node->left);
        _change_size(node->right);
        _change_size(node);
    }
    return _change_balance(node);
}

void AVLTree::_values(Node *node, std::vector<int> &data_values) {
    if (node != nullptr) {
        _values(node->left, data_values);
        data_values.push_back(node->value);
        _values(node->right, data_values);
    }
}

bool AVLTree::empty() const {
    return root == nullptr;
}

bool AVLTree::insert(int value) {
    bool result = true;
    root = _insert(root, value, result);
    return result;
}

bool AVLTree::contains(int value) const {
    return _contains(root, value);
}

std::size_t AVLTree::size() const {
    if (root == nullptr) {
        return 0;
    }
    return root->size;
}

bool AVLTree::remove(int value) {
    bool result = false;
    root = _remove(root, value, result);
    _change_size(root);
    return result;
}

std::vector<int> AVLTree::values() const {
    std::vector<int> data_values;
    data_values.reserve(root->size);
    _values(root, data_values);
    return data_values;
}

int _get_k(int k, Node *node) {
    if (node == nullptr) {
        return 1;
    }
    if (node->right == nullptr) {
        if (k == 1) {
            return node->value;
        } else {
            if (node->left == nullptr) {
                return node->value;
            }
            return _get_k(k - 1, node->left);
        };
    }
    if (k - node->right->size == 1) {
        return node->value;
    }
    if (node->right->size >= k) {
        return _get_k(k, node->right);
    } else {
        if (node->left == nullptr) {
            return node->value;
        }
        return _get_k(k - node->right->size - 1, node->left);
    }
}

int AVLTree::get_k(int k) {
    return _get_k(k, root);
}

AVLTree::~AVLTree() {
    delete root;
}


int _size(Node *node) {
    if (node) {
        return node->size;
    }
    return 0;

}

void _change_size(Node *node) {
    if (node == nullptr) {
        return;
    }
    node->size = _size(node->left) + _size(node->right) + 1;
}

void split(Node *node, Node *&l, Node *&r, int v) {
    if (!node) {
        l = nullptr;
        r = nullptr;
        return;
    }
    if (v <= _size(node->left)) {
        split(node->left, l, node->left, v);
        r = node;
    } else {
        split(node->right, node->right, r, v - _size(node->left) - 1);
        l = node;
    }
    _change_size(node);
}

Node *merge(Node *l, Node *r) {
    if (!l) {
        return r;
    }
    if (!r) {
        return l;
    }
    Node *out;

    if (l->key <= r->key) {
        r->left = merge(l, r->left);
        _change_size(l);
        _change_size(r);
        return r;
        out = r;
    } else {
        l->right = merge(l->right, r);
        _change_size(l);
        _change_size(r);
        return l;
        out = l;
    }
    return out;
}


void cout_ans(Node *node) {
    if (!node) {
        return;
    }
    cout_ans(node->left);
    cout << node->value << " ";
    cout_ans(node->right);
}

Node *swap_ne(Node *node, int l, int r) {
    Node *rightL;
    Node *rightR;
    Node *leftR;
    Node *leftL;
    split(node, rightL, rightR, r);
    split(rightL, leftR, leftL, l - 1);
    leftL = merge(leftL, leftR);
    return merge(leftL, rightR);
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    Node *root = nullptr;
    for (int i = 1; i <= n; i++) {
        root = merge(root, new Node(i));
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        swap_ne(root, l, r);
    }
    cout_ans(root);

}
