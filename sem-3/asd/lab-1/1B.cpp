#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int maxN = 1e5;

// O(n log n), should better - it's easy, use array of used

struct Graph {
    struct edge {
        int from;
        int to;
        int w;

        edge(int from, int to, int w)
                : from(from),
                  to(to),
                  w(w) {
        }

    };

    int n, m;
    int s, t;
    vector<vector<edge>> g;
    vector<bool> used;
    vector<int> topSortOrder;

    void input() {
        cin >> n >> m >> s >> t;
        s--;
        t--;
        g.assign(n, {});
        used.assign(n, false);
        for (int i = 0; i < m; ++i) {
            int b, e, w;
            cin >> b >> e >> w;
            b--;
            e--;
            g[b].push_back(edge(b, e, w));
        }
    }

    void dfs(int v) {
        used[v] = true;
        for (auto e: g[v]) {
            if (!used[e.to])
                dfs(e.to);
        }
        topSortOrder.push_back(v);
    }

    void topSort() {
        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                dfs(i);
            }
        }
        reverse(topSortOrder.begin(), topSortOrder.end());
    }

    vector<int> dp;
    set<int> fromS;

    int getMinWay() {
        dp.assign(n, 1e9);
        dp[s] = 0;
        bool wasVisitS = false;
        for (int v: topSortOrder) {
            if (v == s) {
                wasVisitS = true;
                fromS.insert(s);
                for (auto e: g[v]) {
                    dp[e.to] = min(dp[e.to], dp[e.from] + e.w);
                    fromS.insert(e.to);
                }
            }
            else if (wasVisitS && fromS.contains(v)) {
                for (auto e: g[v]) {
                    dp[e.to] = min(dp[e.to], dp[e.from] + e.w);
                    fromS.insert(e.to);
                }
            }
        }
        return dp[t];
    }

};

int main() {
    Graph g;
    g.input();
    g.topSort();
    int ans = g.getMinWay();
    if (ans == 1e9) {
        cout << "Unreachable";
    } else {
        cout << ans;
    }

    return 0;
}