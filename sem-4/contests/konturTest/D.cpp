#include <iostream>
#include <vector>

using namespace std;

int main() {
    int W = 100 * 500;
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(6, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 6; ++j) {
            cin >> a[i][j];
        }
    }

    vector<vector<bool>> dp(n + 1, vector<bool>(W + 1, false));

    dp[0][0] = true;
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            for (int j = 0; j < 6; ++j) {
                if (w - a[i - 1][j] >= 0) {
                    dp[i][w] = dp[i][w] || dp[i - 1][w - a[i - 1][j]];
                }
            }
        }
    }
    int res = 0;
    for (int i = 0; i < W + 1; ++i) {
        if (dp[n][i]) {
            res++;
        }
    }
    cout << res;
}