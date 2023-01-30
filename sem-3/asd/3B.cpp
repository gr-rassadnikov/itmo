//
// Created by Grigorii Rassadnikov on 25.01.2023.
//

#include <vector>
#include <algorithm>
#include <string>
#include <deque>
#include <map>
#include <set>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <iostream>

using namespace std;
int INF = 1e5;
vector<int> used(3 * INF, 0);
vector<int> d(3 * INF, -1);
vector<int> up(3 * INF, -1);
vector<int> point(3 * INF, 0);

void dfs(int v, vector<vector<int>> &g, int t, int parent, vector<int> &global) {
    d[v] = t;
    up[v] = d[v];
    used[v] = 1;
    int count_child = 0;
    for (auto to: g[v]) {
        if (to == parent) continue;

        if (!used[to]) {
            dfs(to, g, t + 1, v, global);
            up[v] = min(up[v], up[to]);
            count_child++;
            if (up[to] >= d[v] && v != 0 && global[v] == 1) {
                point[v] = 1;
            }
        } else {
            up[v] = min(up[v], d[to]);
        }

    }

}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> global(n, 0);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        c--;
        g.push_back({});
        g[g.size() - 1].push_back(a);
        g[g.size() - 1].push_back(b);
        g[g.size() - 1].push_back(c);
        g[a].push_back(g.size() - 1);
        g[b].push_back(g.size() - 1);
        g[c].push_back(g.size() - 1);
        global.push_back(1);
    }

    dfs(0, g, 0, -1, global);
    int ans = 0;
    for (int i = 0; i < 3 * n; i++) {
        ans += point[i];
    }
    cout << ans << endl;
    for (int i = 0; i < 3 * n; i++) {
        if (point[i] == 1) {
            cout << i + 1 - n << " ";
        }
    }

}
