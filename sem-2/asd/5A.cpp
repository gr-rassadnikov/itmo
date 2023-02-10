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
    vector<pair<long long, int>> tree;

    void init(int n) {
        tree.assign(4 * n, {INT_MAX, -1});
        return;
    }


    void build(int u, int l, int r, vector<long long> &a) {
        if (l + 1 == r) {
            tree[u] = {a[l], l};
            return;
        } else {
            int m = (l + r) / 2;
            build(2 * u + 1, l, m, a);
            build(2 * u + 2, m, r, a);
            if (tree[2 * u + 1].first < tree[2 * u + 2].first) {
                tree[u] = tree[2 * u + 1];
            } else {
                tree[u] = tree[2 * u + 2];
            }
        }
    }

    pair<long long, int> min(int u, int l, int r, int lx, int rx) {
        if (l <= lx && rx <= r) {
            return tree[u];
        } else if (lx >= r || rx <= l) {
            return {INT_MAX, -1};
        } else {
            int m = (lx + rx) / 2;
            auto ll = min(2 * u + 1, l, r, lx, m);
            auto rr = min(2 * u + 2, l, r, m, rx);
            if (ll.first < rr.first) {
                return ll;
            } else {
                return rr;
            }
        }
    }
};

void dfs(int u, vector<vector<int>> &g, vector<long long> &d, vector<int> &vtx, vector<int> &I, int len) {
    d.push_back(len);
    vtx.push_back(u);
    for (int to: g[u]) {
        dfs(to, g, d, vtx, I, len + 1);
        d.push_back(len);
        vtx.push_back(u);
    }
    I[u] = vtx.size() - 1;

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    int root = 0;
    for (int i = 0; i < n - 1; i++) {
        int x;
        cin >> x;
        x--;
        g[x].push_back(i + 1);

    }

    vector<long long> d;
    vector<int> vtx;
    vector<int> I(n);
    dfs(root, g, d, vtx, I, 0);

//    for (int i: d) {
//        cout << i << " ";
//    }
//    cout << "\n";
//    for (int i: vtx) {
//        cout << i << " ";
//    }
//    cout << "\n";
//    for (int i: I) {
//        cout << i << " ";
//    }
//    cout << "\n";

    segtree t;
    t.init(d.size());
    t.build(0, 0, d.size(), d);
    int m;
    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
//        cout << t.min(0, min(I[u], I[v]), 1 + max(I[u], I[v]), 0, d.size()).second << "\n";
        cout << vtx[t.min(0, min(I[u], I[v]), 1 + max(I[u], I[v]), 0, d.size()).second] + 1;
        cout << "\n";
    }


}
