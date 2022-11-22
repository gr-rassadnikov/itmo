//
// Created by Grigorii Rassadnikov on 05.11.2022.
//


#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;
    std::vector<std::vector<bool>> g(n, std::vector<bool>(n, false));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; ++j) {
            char c;
            std::cin >> c;
            if (c == '1') {
                g[i][j] = true;
            } else {
                g[j][i] = true;
            }
        }
    }
    std::vector<int> q(n, 0);
    for (int i = 0; i < n; i++) {
        q[i] = i;
    }
    while (!std::is_sorted(q.begin(), q.end(), [&](int l, int r) {
        if (g[l][r]) {
            return true;
        }
        return false;
    }) || !g[q[n - 1]][q[0]]) {
        std::stable_sort(q.begin(), q.end(), [&](int l, int r) {
            if (g[l][r]) {
                return true;
            }
            return false;
        });
    }
    for (auto i: q) {
        std::cout << i + 1 << " ";
    }


}