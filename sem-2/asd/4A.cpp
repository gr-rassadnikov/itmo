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

using namespace std;

class Node {
public:
    Node *left;
    Node *right;
    const int value;
    int height;
    int size;

    Node(int value);

    ~Node();
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

Node::Node(const int value)
        : left(nullptr), right(nullptr), value(value), height(0), size(1) {
}

Node::~Node() {
    delete left;
    delete right;
}

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    AVLTree tree;
    while (n--) {
        int c, k;
        cin >> c >> k;
        if (c == 1) {
            tree.insert(k);
        } else if (c == 0) {
            cout << tree.get_k(k) << "\n";
        } else {
            tree.remove(k);
        }
    }

}
