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

struct segtree {
    vector<long long> tree;

    void init(int n) {
        tree.assign(4 * n, 0);
    }

    void build(int u, int l, int r, vector<long long> &a) {
        if (l + 1 == r) {
            tree[u] = a[l];
        } else {
            int m = (l + r) / 2;
            build(2 * u + 1, l, m, a);
            build(2 * u + 2, m, r, a);
            tree[u] = tree[2 * u + 1] + tree[2 * u + 2];
        }
    }

    void set(int i, int u, long long ans, int l, int r) {
        int m = (r + l) / 2;
        if (l + 1 == r) {
            tree[u] = ans;
        } else if (i < m) {
            set(i, 2 * u + 1, ans, l, m);
            tree[u] = tree[2 * u + 1] + tree[2 * u + 2];
        } else {
            set(i, 2 * u + 2, ans, m, r);
            tree[u] = tree[2 * u + 1] + tree[2 * u + 2];
        }
    }

    long long summ(int u, int l, int r, int lx, int rx) {
        if (l <= lx && rx <= r) {
            return tree[u];
        } else if (lx >= r || rx <= l) {
            return 0;
        } else {
            int m = (lx + rx) / 2;
            return summ(2 * u + 1, l, r, lx, m) + summ(2 * u + 2, l, r, m, rx);
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
    tree.init(n);
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    tree.build(0, 0, n, a);
    string q;
    while (cin >> q ) {
        if (q == "set") {
            int i;
            long long u;
            cin >> i >> u;
            tree.set(i, 0, u, 0, n);

        } else {
            int l, r;
            cin >> l >> r;
            cout << tree.summ(0, l - 1, r - 1, 0, n) << endl;
        }
    }
}
