#include <vector>
#include <algorithm>
#include <string>
#include <deque>
#include <map>
#include <set>
#include <cmath>
#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

int log(int n) {
    int i = 1;
    int cnt = 0;
    while (i <= n) {
        cnt++;
        i *= 2;
    }
    return cnt - 1;
}

int p(int n, int k) {
    int r = 1;
    while (k > 0) {
        r *= n;
        k--;
    }
    return r;

}

int get(int u, int v, vector<vector<int>> &dp, vector<int> &a) {
    if (u == v) {
        return a[u];
    }
    int j = log(max(u, v) - min(u, v));
    return min(dp[j][min(u, v)], dp[j][max(0, max(u, v) - p(2, j))]);

}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
//    cout << log(1) << log(2) << p(2, 1);
//    return 0;
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    cin >> a[0];
    for (int i = 1; i < n; i++) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
    }
    vector<vector<int>> dp(log(n) + 1, vector<int>(n, 1e9));
    for (int i = 0; i < n - 1; i++) {
        dp[0][i] = min(a[i], a[i + 1]);
    }
    dp[0][n - 1] = a[n - 1];
    for (int k = 1; k < log(n) + 1; k++) {
        for (int i = 0; i < n; i++) {
            dp[k][i] = min(dp[k - 1][i], dp[k - 1][min(i + p(2, k - 1), n - 1)]);
        }
    }
//    for (int i = 0; i < dp.size(); i++) {
//        for (int j = 0; j < dp[0].size(); j++) {
//            cout << dp[i][j] << " ";
//        }
//        cout << "\n";
//    }
//    return 0;

    int u, v;
    cin >> u >> v;
    int i = 0;
    int r = 0;
    int x = u, y = v;

    while (m--) {
        i++;
        r = get(u - 1, v - 1, dp, a);
//        cout << u << " " << v << " " << r << "\n";
        x = u;
        y = v;
        u = ((17 * u + 751 + r + 2 * i) % n) + 1;
        v = ((13 * v + 593 + r + 5 * i) % n) + 1;

    }
    cout << x << " " << y << " " << r << "\n";
}
