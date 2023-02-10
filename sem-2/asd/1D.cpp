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
#define ll long long

struct segtree {
    struct node {
        ll m = INT64_MAX;
        ll add = 0;
        ll set = INT64_MAX;
        // 0 - add
        //1 - set
    };
    vector<node> tree;

    void init(int n) {
        tree.assign(4 * n, node());
    }

    static long long operation(ll a, ll b) {
        if (b < a) {
            return b;
        }
        return a;
    }

    void propogate(int x) {
        if (2 * x + 2 < tree.size()) {
            if (tree[x].set != INT64_MAX) {
                tree[2 * x + 2].set = tree[2 * x + 1].set = tree[x].set;
                tree[2 * x + 1].add = tree[2 * x + 2].add = 0;
            }
            tree[2 * x + 1].add += tree[x].add;
            tree[2 * x + 2].add += tree[x].add;
        }

        if (tree[x].set != INT64_MAX) {
            tree[x].m = tree[x].set;
        }
        tree[x].m += tree[x].add;

        tree[x].add = 0;
        tree[x].set = INT64_MAX;
    }


    void build(int u, int l, int r, vector<long long>& a) {
        if (l + 1 == r) {
            tree[u].m = a[l];
            return;
        }
        else {
            int m = (l + r) / 2;
            build(2 * u + 1, l, m, a);
            build(2 * u + 2, m, r, a);
            tree[u].m = operation(tree[2 * u + 1].m, tree[2 * u + 2].m);
        }
    }

    void set(int l, int r, ll v, int x, int lx, int rx) {
        propogate(x);
        if (l >= rx || lx >= r) {
            return;
        }
        else if (lx >= l && rx <= r) {
            tree[x].set = v;
            tree[x].add = 0;
        }
        else {
            int m = (lx + rx) / 2;
            set(l, r, v, 2 * x + 1, lx, m);
            set(l, r, v, 2 * x + 2, m, rx);
            propogate(2 * x + 1);
            propogate(2 * x + 2);
            tree[x].m = operation(tree[2 * x + 1].m, tree[2 * x + 2].m);
        }
    }

    void change(int l, int r, ll v, int x, int lx, int rx) {
        propogate(x);
        if (l >= rx || lx >= r) {
            return;
        }
        else if (lx >= l && rx <= r) {
            tree[x].add += v;
        }
        else {
            int m = (lx + rx) / 2;
            change(l, r, v, 2 * x + 1, lx, m);
            change(l, r, v, 2 * x + 2, m, rx);
            propogate(2 * x + 1);
            propogate(2 * x + 2);
            tree[x].m = operation(tree[2 * x + 1].m, tree[2 * x + 2].m);
        }
    }

    long long min(int u, int l, int r, int lx, int rx) {
        propogate(u);
        if (l <= lx && rx <= r) {
            return tree[u].m;
        }
        else if (lx >= r || rx <= l) {
            return INT64_MAX;
        }
        else {
            int m = (lx + rx) / 2;
            return operation(min(2 * u + 1, l, r, lx, m), min(2 * u + 2, l, r, m, rx));
        }
    }
};

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>> n;
    segtree tree;
    tree.init(n);
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    tree.build(0, 0, n, a);
    string q;
    while (cin>> q) {
        // cout « "\n";
        // for(auto i: tree.tree){
        // cout « i.m « " ";
        // }
        if (q == "set") {
            int i, j;
            long long x;
            cin >> i >>j>> x;
            tree.set(i - 1, j, x, 0, 0, n);
        }
        else if (q == "add") {
            int i, j;
            long long x;
            cin>> i>> j>> x;
            tree.change(i - 1, j, x, 0, 0, n);
        }
        else {
            int l, r;
            cin>> l>> r;
            cout<< tree.min(0, l - 1, r, 0, n)<< endl;
        }
    }
}