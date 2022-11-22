
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iomanip>

bool isEmpty(const std::vector<std::vector<int>> &g) {
    for (const auto &i: g) {
        if (!i.empty()) {
            return false;
        }
    }
    return true;
}

std::vector<std::vector<int>> popUV(std::vector<std::vector<int>> g) {
    for (int i = g.size() - 1; i >= 0; i--) {
        if (!g[i].empty()) {
            int to = g[i].back();
            g[i].pop_back();
            for (int j = 0; j < g[to].size(); j++) {
                if (g[to][j] == i) {
                    g[to].erase(g[to].begin() + j);
                    break;
                }
            }
            return g;
        }
    }
    return g;
}

std::vector<std::vector<int>> compressUV(std::vector<std::vector<int>> g) {
    int v = 0;
    for (int i = g.size() - 1; i >= 0; i--) {
        if (!g[i].empty()) {
            v = i;
            break;
        }
    }
    int u = g[v].back();
    for (int to: g[v]) {
        if (to != u && std::find(g[u].begin(), g[u].end(), to) == g[u].end()) {
            g[u].push_back(to);
        }
    }
    for (int i = 0; i < g.size(); i++) {
        if (i != u) {
            for (int j = 0; j < g[i].size(); j++) {
                if (g[i][j] == v) {
                    g[i].erase(g[i].begin() + j);
                    if (std::find(g[i].begin(), g[i].end(), u) == g[i].end()) {
                        g[i].push_back(u);
                    }
                    break;
                }
            }
        } else {
            for (int j = 0; j < g[i].size(); j++) {
                if (g[i][j] == v) {
                    g[i].erase(g[i].begin() + j);
                    break;
                }
            }
        }
    }
    g.erase(g.begin() + v);
    return g;
}

std::vector<int> minus(std::vector<int> l, std::vector<int> r) {
    std::vector<int> x(std::max(l.size(), r.size()), 0);
    for (int i = 0; i < l.size(); i++) {
        x[i] += l[i];
    }
    for (int i = 0; i < r.size(); i++) {
        x[i] -= r[i];
    }
    return x;
}

std::vector<int> hrom(std::vector<std::vector<int>> g) {
    if (isEmpty(g)) {
        std::vector<int> x(g.size() + 1, 0);
        x[x.size() - 1] = 1;
        return x;
    }
    return minus(hrom(popUV(g)), hrom(compressUV(g)));
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;
    int m;
    std::cin >> m;
    std::vector<std::vector<int>> g(n);
    int k = 1;
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }

    std::vector<int> x = hrom(g);
    std::cout << n << "\n";
    std::reverse(x.begin(), x.end());
    for (int i: x) {
        std::cout << i << " ";
    }
}
//4 5
//1 2
//1 3
//2 3
//2 4
//3 4


//7 14
//1 2
//2 3
//3 4
//4 5
//5 6
//6 7
//7 1
//7 4
//7 2
//6 1
//6 2
//5 2
//5 3
//4 1