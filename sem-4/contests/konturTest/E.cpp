#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 2, vector<int>(m + 2, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            char c;
            cin >> c;
            a[i][j] = c - '0';
        }
    }
    vector<vector<int>> h1(n + 2, vector<int>(m + 2, 0));
    vector<vector<int>> h2(n + 2, vector<int>(m + 2, 0));
    vector<vector<int>> h3(n + 2, vector<int>(m + 2, 0));
    vector<vector<int>> h4(n + 2, vector<int>(m + 2, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            h1[i][j] = max(a[i][j], max(h1[i - 1][j], h1[i][j - 1]));
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= 1; --j) {
            h2[i][j] = max(a[i][j], max(h2[i - 1][j], h2[i][j + 1]));
        }
    }

    for (int i = n; i >= 1; --i) {
        for (int j = 1; j <= m; ++j) {
            h3[i][j] = max(a[i][j], max(h3[i + 1][j], h3[i][j - 1]));
        }
    }

    for (int i = n; i >= 1; --i) {
        for (int j = m; j >= 1; --j) {
            h4[i][j] = max(a[i][j], max(h4[i + 1][j], h4[i][j + 1]));
        }
    }

    int res = 1e9;
    pair<int, int> res_pair = {-1, -1};
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int k1 = h1[i - 1][j - 1];
            int k2 = h2[i - 1][j + 1];
            int k3 = h3[i + 1][j - 1];
            int k4 = h4[i + 1][j + 1];
            int k = max(max(k1, k2), max(k3, k4));
            if (k < res) {
                res = k;
                res_pair = {i, j};
            }
        }
    }
    cout << res_pair.first << " " << res_pair.second;

}