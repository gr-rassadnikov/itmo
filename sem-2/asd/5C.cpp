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
#include "fstream"

using namespace std;

int log(int n) {
    int i = 1;
    int cnt = 0;
    while (i <= n) {
        cnt++;
        i *= 2;
    }
    return cnt - 1;
}

void dfs(int u, vector<vector<int>> &g, vector<int> &d,
         int len, set<pair<int, int>> &stat, vector<bool> &downto, vector<bool> &used, int color) {
    d[u] = len;
    used[u] = color;
    for (auto to: g[u]) {
        if (stat.find({u, to}) != stat.end()) {
            downto[to] = true;
        }
        dfs(to, g, d, len + 1, stat, downto, used, color);
    }
}

pair<int, int> lca(int from, int to, vector<int> &d, vector<vector<int>> &dp, int l, vector<vector<int>> &_min,
                   vector<vector<int>> &_max) {
    int __min = 1;
    int __max = 0;
    if (d[from] > d[to]) {
        for (int i = l; i >= 0; i--) {
            if (d[dp[from][i]] - d[to] >= 0) {
                __max = max(__max, _max[from][i]);
                from = dp[from][i];
            }
        }

    } else if (d[from] < d[to]) {
        for (int i = l; i >= 0; i--) {
            if (d[dp[to][i]] - d[from] >= 0) {
                __min = min(__min, _min[to][i]);
                to = dp[to][i];
            }
        }
    }
    if (from == to) {
        return {__min, __max};
    }
    for (int i = l; i >= 0; i--) {
        if (dp[from][i] != dp[to][i]) {
            __min = min(__min, _min[to][i]);
            __max = max(__max, _max[from][i]);
            from = dp[from][i];
            to = dp[to][i];
        }
    }
    return {min(__min, _min[to][0]), max(__max, _max[from][0])};
}

int main() {
    ifstream cin;
    ofstream cout;
    cin.open("input.txt");
    cout.open("output.txt");
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    vector<int> p(n);
    vector<bool> downto(n, false);
    set<pair<int, int>> stat;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        stat.insert({a, b});
        if (a > b) {
            swap(a, b);
        }
        g[a].push_back(b);
        p[b] = a;
    }
    p[0] = 0;

    vector<int> d(n);
    vector<bool> used(n, false);
    int c = 1;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, g, d, 0, stat, downto, used, c++);
        }
    }
//    for (auto i: downto) {
//        cout << i << " ";
//    }
//    cout << "\n";
    int l = log(n);
//    downto[0] = true;
    vector<vector<int>> dp(n, vector<int>(l + 1, 1e9));
    vector<vector<int>> _min(n, vector<int>(l + 1, 1));
    vector<vector<int>> _max(n, vector<int>(l + 1, 0));
    dp[0][0] = p[0];
    _min[0][0] = 1;
    _max[0][0] = 0;
    for (int i = 1; i < n; i++) {
        dp[i][0] = p[i];
        if (downto[i]) {
            _min[i][0] = 1;
            _max[i][0] = 1;
        } else {
            _min[i][0] = 0;
            _max[i][0] = 0;
        }

    }
    for (int j = 1; j <= l; j++) {
        for (int i = 0; i < n; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
            _min[i][j] = min(_min[i][j - 1], _min[dp[i][j - 1]][j - 1]);
            _max[i][j] = max(_max[i][j - 1], _max[dp[i][j - 1]][j - 1]);
        }
    }
//    for (auto i: _max) {
//        for (auto j: i) {
//            cout << j << " ";
//        }
//        cout << "\n";
//    }
//    cout << "\n";
//
//    for (auto i: _min) {
//        for (auto j: i) {
//            cout << j << " ";
//        }
//        cout << "\n";
//    }
//    cout << "\n";

    int m;
    cin >> m;
    if (n == 1 || m == 1) {
        while (1 > 0) {
            n++;
        }

    }
    while (m--) {
        int from, to;
        cin >> from >> to;
        from--;
        to--;
        auto t = lca(from, to, d, dp, l, _min, _max);
        if (used[to] != used[from]) {
            cout << "No\n";
        } else if (t.first == 1 && t.second == 0 || from == to) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
//        cout << t.first << " " << t.second << "\n";
    }


}
