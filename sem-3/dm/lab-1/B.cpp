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
            g[i][j] = c == '1';
            g[j][i] = g[i][j];
        }
    }
    std::deque<int> q;

    for (int v = 0; v < n; v++) {
        q.push_back(v);
    }
    for (int it = 0; it < n * (n - 1) / 2 + 1; ++it) {
        if (!g[q.front()][*(q.begin() + 1)]) {
            auto ind = q.begin() + 2;
            while (ind != q.end() && ind + 1 != q.end() && (!g[q.front()][*(ind)] || !g[*(q.begin() + 1)][*(ind + 1)])) {
                ++ind;
            }
            if (ind == q.end() || ind + 1 == q.end()) {
                ind = q.begin() + 2;
                while (!g[q.front()][*ind]) {
                    ind++;
                }
            }
            reverse(q.begin() + 1, ind + 1);
        }

        q.push_back(q.front());
        q.pop_front();
    }
    for (auto i: q) {
        std::cout << i + 1 << " ";
    }
}