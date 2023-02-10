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

int log(int n) {
    int i = 1;
    int cnt = 0;
    while (i <= n) {
        cnt++;
        i *= 2;
    }
    return cnt - 1;
}

void dfs(pair<int, int> u, vector<vector<pair<int, int>>> &g, vector<int> &d,
         int len) {
    d[u.first] = len;
    for (auto to: g[u.first]) {
        dfs(to, g, d, len + 1);
    }
}

int lca(int v, int u, vector<int> &d, vector<vector<int>> &dp, int l, vector<vector<int>> &ans) {
    int mm = INT_MAX;
    if (d[v] > d[u]) {
        swap(v, u);
    }
    for (int i = l; i >= 0; i--) {
        if (d[dp[u][i]] - d[v] >= 0) {
            mm = min(mm, ans[u][i]);
            u = dp[u][i];
        }
    }
    if (v == u) {
        return mm;
    }
    for (int i = l; i >= 0; i--) {
        if (dp[v][i] != dp[u][i]) {
            mm = min(mm, ans[u][i]);
            mm = min(mm, ans[v][i]);
            v = dp[v][i];
            u = dp[u][i];
        }
    }
    return min(mm, min(ans[u][0], ans[v][0]));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> g(n);
    vector<pair<int, int>> p(n);
    pair<int, int> root = {0, 0};
    for (int i = 0; i < n - 1; i++) {
        int x;
        int y;
        cin >> x >> y;
        x--;
        g[x].push_back({i + 1, y});
        p[i + 1] = {x, y};
    }
    p[0] ={0,INT_MAX};

    vector<int> d(n);
    dfs(root, g, d, 0);
    int l = log(n);
    vector<vector<int>> dp(n, vector<int>(l + 1, INT_MAX));
    vector<vector<int>> ans(n, vector<int>(l + 1, INT_MAX));
    for (int i = 0; i < n; i++) {
        dp[i][0] = p[i].first;
        ans[i][0] = p[i].second;
    }
    for (int j = 1; j <= l; j++) {
        for (int i = 0; i < n; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
            ans[i][j] = min(ans[i][j - 1], ans[dp[i][j - 1]][j - 1]);
        }
    }
//    for (auto i: ans) {
//        for (auto j: i) {
//            cout << j << " ";
//        }
//        cout << "\n";
//    }

    int m;
    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        cout << lca(u, v, d, dp, l, ans) << "\n";
    }


}
