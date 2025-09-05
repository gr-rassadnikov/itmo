#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> objects;

    for (int i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        objects.push_back(std::make_pair(x, y));
    }

    int m;
    std::cin >> m;

    for (int i = 0; i < m; i++) {
        int x, k;
        std::cin >> x >> k;

        std::vector<std::pair<int, int>> dist;
        for (const auto& obj : objects) {
            dist.emplace_back(std::abs(obj.first - x), obj.second);
        }

        std::sort(dist.begin(), dist.end(), [](const auto& a, const auto& b) {
            return a.first < b.first;
        });

        std::vector<std::pair<int, int>> f(dist.begin(), dist.begin() + k);

        if (k >= dist.size() || dist[k - 1] != dist[k]) {
            double avg = 0;
            for (const auto& pair : f) {
                avg += pair.second;
            }
            avg /= k;

            std::cout << std::fixed << std::setprecision(7) << avg << std::endl;
        } else {
            std::cout << std::fixed << std::setprecision(7) << -1.0 << std::endl;
        }
    }

    return 0;
}