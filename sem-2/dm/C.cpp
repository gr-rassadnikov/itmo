#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <deque>
#include <map>

using namespace std;

void dfs(int v, vector<vector<int>> &g,
         vector<bool> &used) {
    used[v] = true;
    for (int i: g[v]) {
        if (!used[i]) {
            dfs(i, g, used);
        }
    }
}

bool Etrip(int v, vector<map<char, vector<int>>> &g, vector<int> &used, vector<int> &vv, vector<bool> &used_0) {
    used[v] = 0;
    for (auto &j: g[v]) {
        for (int i: j.second) {
            if (used[i] == -1) {
                Etrip(i, g, used, vv, used_0);
            }
        }
    }
    used[v] = 1;
    vv.push_back(v);
    return true;
}

int main() {
    ifstream cin("problem5.in");
    ofstream cout("problem5.out");
    int mod = 1e9 + 7;
    int n, m, k, l;
    cin >> n >> m >> k >> l;
    vector<bool> end(n, false);
    for (int i = 0; i < k; i++) {
        int a;
        cin >> a;
        a--;
        end[a] = true;
    }
    vector<map<char, vector<int>>> g(n);
    vector<vector<int>> gr(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        a--;
        b--;
        g[a][c].push_back(b);
    }
    vector<int> used(n, -1);
    vector<bool> used_0(n, false);
    vector<vector<int>> d(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= l; j++) {
            d[i].push_back(0);
        }
    }
    deque<vector<int>> Q = {{0}};
    map<vector<int>, int> dict;
    dict[{0}] = 0;
    vector<map<char, vector<int>>> new_g(n);
    vector<bool> new_end(n, false);
    new_end[0] = end[0];
    while (!Q.empty()) {
        vector<int> v = Q.front();
        vector<int> new_g_to;
        for (char rebro = 'a'; rebro <= 'z'; rebro++) {
            new_g_to.clear();
            bool is = false;
            bool fl = false;
            for (int i: v) {
                for (int to: g[i][rebro]) {
                    new_g_to.push_back(to);
                    fl = true;
                    is = end[to] || is;
                }
            }
            if (fl) {
                std::sort(new_g_to.begin(), new_g_to.end());
                if (dict.find(new_g_to) != dict.end()) {
                    new_g[dict[v]][rebro].push_back(dict[new_g_to]);
                } else {
                    new_end[dict.size()] = is;
                    dict[new_g_to] = dict.size();
                    Q.push_back(new_g_to);
                    new_g[dict[v]][rebro].push_back(dict[new_g_to]);
                }
            }
        }
        Q.pop_front();
    }


    vector<int> vv;


    bool s = Etrip(0, new_g, used, vv, used_0);

    d[0][0] = 1;
    for (int _l = 0; _l < l; _l++) {
        for (int i = vv.size() - 1; i >= 0; i--) {
            for (auto &j: new_g[vv[i]]) {
                for (int to: j.second) {
                    d[to][_l + 1] = (d[to][_l + 1] + d[vv[i]][_l]) % mod;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (new_end[i]) {
            ans = (ans + d[i][l]) % mod;
        }
    }
    cout << ans % mod;
    return 0;
}
