#include <iostream>
#include <utility>


template<typename T>
class List {
private:

    struct Node {
        Node *prev;
        Node *next;
        T value;

        explicit Node(T value, Node *prev = nullptr, Node *next = nullptr)
                : value(std::move(value)),
                  prev(prev),
                  next(next) {
        }

    };

    Node *backNode;

public:

    void push_back(const T &value) {
        if (!backNode) {
            backNode = new Node(value);
        } else {
            auto *newNode = new Node(value, backNode);
            backNode->next = newNode;
            backNode = newNode;
        }
    }

    auto toString() -> std::string {
        std::string str;
        auto *now = backNode;
        while (now->prev) {
            now = now->prev;
        }

        while (now) {
            str += now->value + " ";
            now = now->next;
        }
        return str;
    }

    List() : backNode(nullptr) {
    }

};


int main() {
    List<std::string> list;
    list.push_back("1");
    list.push_back("2");
    list.push_back("3");
    list.push_back("4");
    std::cout << list.toString();


}
