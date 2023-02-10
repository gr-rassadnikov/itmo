#include <iostream>
#include <vector>

using namespace std;
#define ll long long

struct segtree {

    vector<int> d;

    void init(int n) {
        d.assign(4 * n, INT_MIN);
    }

    void build(vector<int> &a, int v, int lx, int rx) {
        if (lx + 1 == rx) {
            d[v] = a[lx];
            return;
        } else {
            int m = (lx + rx) / 2;
            build(a, 2 * v + 1, lx, m);
            build(a, 2 * v + 2, m, rx);
            d[v] = max(d[2 * v + 1], d[2 * v + 2]);
        }
    }

    void set(int v, int i, int ans, int lx, int rx) {
        int m = (lx + rx) / 2;
        if (lx + 1 == rx) {
            d[v] = ans;
        } else if (i < m) {
            set(2 * v + 1, i, ans, lx, m);
            d[v] = min(d[2 * v + 1], d[2 * v + 2]);
        } else {
            set(2 * v + 2, i, ans, m, rx);
            d[v] = min(d[2 * v + 1], d[2 * v + 2]);
        }
    }

    long long maximum(int l, int r, int v, int lx, int rx) {
        if (l <= lx && rx <= r) {
            return d[v];
        } else if (lx >= r || rx <= l) {
            return INT_MIN;
        } else {
            int m = (rx + lx) / 2;
            return max(maximum(l, r, 2 * v + 1, lx, m), maximum(l, r, 2 * v + 2, m, rx));
        }
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    segtree tree;
    tree.init(m);
    tree.build(a, 0, 0, m);
    int q;
    cin >> q;
    while (q--) {
        int x1, x2, y1, y2, k;
        cin >> x1 >> y1 >> x2 >> y2 >> k;
        int h = ((n - x1) / k) * k + x1;
        int maxi = tree.maximum(min(y1, y2) - 1, max(y1, y2), 0, 0, m);

         if (maxi >= h || abs(h - x2) % k != 0 || abs(y1 - y2) % k != 0) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }

    }


    return 0;
}
