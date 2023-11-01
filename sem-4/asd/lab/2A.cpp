#include<iostream>
#include <vector>
#include <deque>


using namespace std;

class G {
    struct edge {
        int a, b, c, f, ind, flag;
    };
    vector<vector<edge>> g;
    vector<int> d;
    deque<int> q;

    int n, m;
    int s, t;
    int F;


public:

    void in() {
        cin >> n >> m;
        s = 0;
        t = n - 1;
        g.assign(n, {});
        for (int i = 0; i < m; ++i) {
            int aC, bC, cC;
            cin >> aC >> bC >> cC;
            aC--;
            bC--;
            g[aC].push_back({aC, bC, cC, 0, (int) g[bC].size(), i});
            g[bC].push_back({bC, aC, cC, 0, (int) g[aC].size() - 1, -1});

        }
    }

    bool bfs() {
        d.assign(n, -1);
        d[s] = 0;
        q.push_back(s);
        while (!q.empty()) {
            int node = q.front();
            q.pop_front();
            for (auto &to: g[node]) {
                if (d[to.b] == -1 && to.f < to.c) {
                    d[to.b] = d[node] + 1;
                    q.push_back(to.b);
                }
            }
        }
        return d[t] >= 0;
    }

    int flag = true;
    vector<int> capacity;

    int dfs(int node, int f = 1e9) {
        if (node == t) return f;
        if (f == 0) return 0;
        for (int i = capacity[node]; i < g[node].size(); i++) {
            capacity[node]++;
            auto &to = g[node][i];
            if (d[to.b] == d[node] + 1) {
                int delta = dfs(to.b, min(f, to.c - to.f));
                if (delta) {
                    to.f += delta;
                    g[to.b][to.ind].f -= delta;
                    if (flag) F += delta;
                    flag = false;
                    return delta;
                }
            }
        }
        return 0;
    }


    void solve() {
        F = 0;
        capacity.assign(n, 0);
        while (true) {
            if (!bfs()) break;
            capacity.assign(n, 0);
            flag = true;
            while (dfs(s)) {
                flag = true;
            }
        }
    }


    void out() {
        cout << F << "\n";
        vector<pair<int, int>> ans;
        for (const auto &i: g) {
            for (auto v: i) {
                if (v.flag >= 0) {
                    ans.push_back({v.flag, v.f});
                }
            }
        }
        std::sort(ans.begin(), ans.end());
        for (auto e: ans) {
            cout << e.second << "\n";
        }
    }

};

int main() {
    G g;
    g.in();
    g.solve();
    g.out();
}
