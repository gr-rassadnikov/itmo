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

int C = 500000 + 1;

struct node {
    int color = 0;
    int cntBlack = 0;
    int colorRight = 0;
    int colorLeft = 0;
    int sum = 0;
    int new_color = -1;

    explicit node(int color, int cntBlack, int colorRight, int colorLeft, int new_color)
            : color(color), cntBlack(cntBlack), colorLeft(colorLeft),
              colorRight(colorRight), new_color(new_color) {}


    node() = default;
};

struct segtree {
    vector<node> tree;

    void init() {
        tree.assign(4 * (C * 2 + 1), node());
    }


    void set(int u, int color, int from, int to, int l, int r) {
        if (from <= l && r <= to) {
            tree[u] = node(color, color, color, color, color);
            if (color == 1) {
                tree[u].sum = r - l;
            } else {
                tree[u].sum = 0;
            }
        } else if (r <= from || l >= to) {
            return;
        } else {
            int m = (r + l) / 2;
            if (tree[u].new_color != -1) {
                tree[2 * u + 1] = node(tree[u].new_color, tree[u].new_color, tree[u].new_color, tree[u].new_color,
                                       tree[u].new_color);
                tree[2 * u + 2] = node(tree[u].new_color, tree[u].new_color, tree[u].new_color, tree[u].new_color,
                                       tree[u].new_color);
                if (tree[u].new_color == 1) {
                    tree[2 * u + 1].sum = m - l;
                    tree[2 * u + 2].sum = r - m;
                }
                tree[u].new_color = -1;
            }
            set(2 * u + 1, color, from, to, l, m);
            set(2 * u + 2, color, from, to, m, r);
            tree[u].color = -1;
            tree[u].cntBlack = tree[2 * u + 1].cntBlack + tree[2 * u + 2].cntBlack;
            if (tree[2 * u + 1].colorRight == tree[2 * u + 2].colorLeft && tree[2 * u + 2].colorLeft == 1) {
                tree[u].cntBlack--;
            }
            tree[u].sum = tree[2 * u + 1].sum + tree[2 * u + 2].sum;
            tree[u].colorLeft = tree[2 * u + 1].colorLeft;
            tree[u].colorRight = tree[2 * u + 2].colorRight;
        }
    }

};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    segtree tree;
    tree.init();
    while (n--) {
        int x, l;
        char q;
        cin >> q;
        cin >> x >> l;
        int from = x + C;
        int to = x + l + C;

        if (q == 'W') {
            tree.set(0, 0, from, to, 0, 2 * C + 1);
        } else {
            tree.set(0, 1, from, to, 0, 2 * C + 1);
        }
        cout << tree.tree[0].cntBlack << " " << tree.tree[0].sum << "\n";
    }
}
