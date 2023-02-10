#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <deque>
#include <map>
#include <set>

using namespace std;

void dfs(int v, vector<map<char, int>> &g, vector<bool> &used) {
    used[v] = true;
    for (auto to: g[v]) {
        if (!used[to.second]) {
            dfs(to.second, g, used);
        }
    }
}

int main() {
    ifstream cin("minimization.in");
    ofstream cout("minimization.out");

    int n, m, k;
    cin >> n >> m >> k;
    vector<bool> term(n + 1, false);
    for (int i = 0; i < k; i++) {
        int a;
        cin >> a;
        term[a] = true;
    }
    set<char> alfavit;

    vector<map<char, int>> g(n + 1);
    vector<map<char, vector<int>>> g_(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        g[a][c] = b;
        alfavit.insert(c);
    }
    for (int i = 0; i < n + 1; i++) {
        for (char c: alfavit) {
            if (g[i].find(c) == g[i].end()) {
                g[i][c] = 0;
            }
        }
    }
    for (int i = 0; i < n + 1; i++) {
        for (auto h: g[i]) {
            if (g_[h.second].find(h.first) != g_[h.second].end()) {
                g_[h.second][h.first].push_back(i);
            } else {
                g_[h.second][h.first] = {i};
            }
        }
    }

    vector<bool> used(n + 1, false);
//    2
    dfs(1, g, used);
//    3
    deque<pair<int, int>> Q;
    vector<vector<bool>> table(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            if (!table[i][j] && term[i] != term[j]) {
                table[i][j] = true;
                table[j][i] = true;
                Q.push_back({i, j});
            }
        }
    }
//    4
    while (!Q.empty()) {
        int u = Q.front().first;
        int v = Q.front().second;
        Q.pop_front();
        for (auto c: alfavit) {
            for (int r: g_[u][c]) {
                for (int s: g_[v][c]) {
                    if (!table[r][s]) {
                        table[r][s] = true;
                        table[s][r] = true;
                        Q.push_back(make_pair(r, s));
                    }
                }
            }

        }
    }

    vector<int> color(n + 1, -1);
    for (int i = 0; i < n + 1; i++) {
        if (!table[0][i]) {
            color[i] = 0;
        }
    }
    int cnt = 0;
    for (int i = 1; i < n + 1; i++) {
        if (used[i] && color[i] == -1) {
            cnt++;
            color[i] = cnt;
            for (int j = i + 1; j < n + 1; j++) {
                if (!table[i][j]) {
                    color[j] = cnt;
                }
            }
        }
    }
    /*
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            cout << table[i][j];
        }
        cout << "\n";
    }
    for (int i = 0; i < color.size(); i++) {
        cout << i << " " << color[i];
        cout << "\n";
    }
    for (int i = 0; i < term.size(); i++) {
        cout << i << " " << term[i];
        cout << "\n";
    }
     */
    int nn = cnt;
    int mm = 0;
    int kk = 0;
//    for (auto i: color) {
//        if (i == -1) {
//            while (true) {
//                cnt++;
//            }
//        }
//    }
    vector<map<char, int>> rebra(nn + 1);
    vector<bool> end(nn + 1, false);
    for (int v = 0; v < n + 1; v++) {
        int new_v = color[v];
        if (new_v == -1) {
            continue;
        }
//        cout << "--" << v << new_v  << term[v] << end[new_v]<< "\n";
        if (term[v] && !end[new_v]) {
            end[new_v] = true;
        }
        for (auto i: g[v]) {
            int new_to = color[i.second];
            if (rebra[new_v].find(i.first) == rebra[new_v].end()) {
                rebra[new_v][i.first] = new_to;
            }

        }
    }
    for (int i = 1; i < nn + 1; i++) {
        if (end[i]) {
            kk++;
        }
    }
    for (int i = 1; i < nn + 1; i++) {
        for (auto to: rebra[i]) {
            if (to.second != 0) {
                mm++;
            }
        }
    }
    cout << nn << " " << mm << " " << kk << "\n";

    for (int i = 1; i < nn + 1; i++) {
        if (end[i]) {
            cout << i << " ";
        }
    }
    cout << "\n";
    for (int i = 1; i < nn + 1; i++) {
        for (auto to: rebra[i]) {
            if (to.second != 0) {
                cout << i << " " << to.second << " " << to.first << "\n";
            }
        }
    }

    return 0;
}
/*
8 16 2
6 7
1 2 b
2 1 b
1 8 a
2 8 a
8 3 a
8 3 b
3 5 a
3 6 b
4 5 a
4 6 b
5 6 a
5 7 b
6 6 a
6 7 b
7 7 a
7 7 b
 */
