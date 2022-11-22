
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iomanip>


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
        k = std::max(k, static_cast<int>((g[a - 1].size() / 2) * 2 + 1));
        k = std::max(k, static_cast<int>((g[b - 1].size() / 2) * 2 + 1));
    }
    std::deque<int> q = {0};

    std::vector<int> c(n, -1);
    c[0] = 0;

    while (!q.empty()) {
        int x = q.front();
        q.pop_front();
        for (int i: g[x]) {
            std::vector<bool> used(k, false);
            if (c[i] == -1) {
                for (int j: g[i]) {
                    if (c[j] != -1) {
                        used[c[j]] = true;
                    }
                }
                int ind = 0;
                for (bool t: used) {
                    if (!t) {
                        break;
                    }
                    ind++;
                }
                c[i] = std::min(ind, k - 1);
                q.push_back(i);

            }
        }
    }

    std::cout << k << "\n";
    for (int i: c) {
        std::cout << i + 1 << "\n";
    }
}
//7 8
//1 4
//4 2
//2 6
//6 3
//3 7
//4 5
//5 6
//5 2