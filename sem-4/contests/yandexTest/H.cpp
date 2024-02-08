#include <iostream>
#include <vector>

using namespace std;

bool can(long long m, long long t, int n, vector<vector<pair<long long, long long>>> &d) {
    for (int i = 0; i < n; ++i) {
        long long min_cost = 1e18 + 1;
        for (auto j: d[i]) {
            if (j.second >= m && j.first < min_cost) {
                min_cost = j.first;
            }
        }
        if (min_cost == (long long) 1e18) {
            return false;
        }
        t -= min_cost;
    }
    return t >= 0;
}

int main() {
    int n;
    long long t;
    cin >> n >> t;
    vector<vector<pair<long long, long long>>> d(n);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            long long p, h;
            cin >> p >> h;
            d[i].push_back(make_pair(p, h));
        }
    }

    long long left = 0;
    long long right = 1e18;
    while (left < right + 1) {
        long long m = (left + right) / 2;
        if (!can(m, t, n, d)) {
            right = m - 1;
        } else {
            left = m + 1;
        }
    }
    cout << ((left - 1 > (long long) 0) ? left - 1 : 0);

}