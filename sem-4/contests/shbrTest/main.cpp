#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <deque>
#include <map>
#include <set>
#include <cmath>
#include <iomanip>

using namespace std;

struct Segtree {

    vector<pair<long long, int>> mn;
    vector<pair<long long, int>> mx;
    vector<set<int>> a;
    vector<long long> r;
    int m;

    Segtree(int n, int m) : m(m) {
        mn.assign(4 * n, {1e18, -1});
        mx.assign(4 * n, {-1e18, -1});
        a.assign(n, {});
        r.assign(n, 0);
        build(0, 0, n);
    }

    void build(int v, int lx, int rx) {
        if (lx + 1 == rx) {
            mn[v] = {0, lx};
            mx[v] = mn[v];
        } else {
            int mid = (lx + rx) / 2;
            build(2 * v + 1, lx, mid);
            build(2 * v + 2, mid, rx);
            mn[v] = myMin(mn[2 * v + 1], mn[2 * v + 2]);
            mx[v] = myMax(mx[2 * v + 1], mx[2 * v + 2]);
        }
    }

    void reset(int v, int i, int lx, int rx) {
        int mid = (lx + rx) / 2;
        if (lx + 1 == rx) {
            r[i]++;
            a[i].clear();
            mn[v] = {m * r[i], i};
            mx[v] = mn[v];
        } else if (i < mid) {
            reset(2 * v + 1, i, lx, mid);
            mn[v] = myMin(mn[2 * v + 1], mn[2 * v + 2]);
            mx[v] = myMax(mx[2 * v + 1], mx[2 * v + 2]);
        } else {
            reset(2 * v + 2, i, mid, rx);
            mn[v] = myMin(mn[2 * v + 1], mn[2 * v + 2]);
            mx[v] = myMax(mx[2 * v + 1], mx[2 * v + 2]);
        }
    }

    void disable(int v, int i, int j, int lx, int rx) {
        int mid = (lx + rx) / 2;
        if (lx + 1 == rx) {
            a[i].insert(j);
            mn[v] = {(m - a[i].size()) * r[i], i};
            mx[v] = mn[v];
        } else if (i < mid) {
            disable(2 * v + 1, i,j, lx, mid);
            mn[v] = myMin(mn[2 * v + 1], mn[2 * v + 2]);
            mx[v] = myMax(mx[2 * v + 1], mx[2 * v + 2]);
        } else {
            disable(2 * v + 2, i,j, mid, rx);
            mn[v] = myMin(mn[2 * v + 1], mn[2 * v + 2]);
            mx[v] = myMax(mx[2 * v + 1], mx[2 * v + 2]);
        }
    }

    pair<long long, int> myMax(pair<long long, int> lhs, pair<long long, int> rhs) {
        if (lhs.first == rhs.first) {
            return lhs;
        }
        return max(lhs, rhs);
    }

    pair<long long, int> myMin(pair<long long, int> lhs, pair<long long, int> rhs) {
        return min(lhs, rhs);
    }

    int getMin() {
        return mn[0].second;
    }

    int getMax() {
        return mx[0].second;
    }

    int getMn() {
        return mn[0].first;
    }

    int getMx() {
        return mx[0].first;
    }
};

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    Segtree segtree(n, m);
    while (q--) {
        string str;
        cin >> str;
        if (str == "DISABLE") {
            int i, j;
            cin >> i >> j;
            i--;
            j--;
            segtree.disable(0, i, j, 0, n);
        } else if (str == "RESET") {
            int i;
            cin >> i;
            i--;
            segtree.reset(0, i, 0, n);
        } else if (str == "GETMAX") {
            cout << segtree.getMax() + 1 << "\n";
        } else {
            cout << segtree.getMin() + 1 << "\n";
        }
    }

}