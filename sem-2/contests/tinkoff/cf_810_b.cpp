#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;
#define ll long long


int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        int summ = 0;
        int min_pair = INT_MAX;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            summ += a[i];
        }
        vector<int> cnt(n, 0);
        set<pair<int, int>> s;
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            if (s.find(make_pair(y, x)) == s.end()) {
                cnt[x] += 1;
                cnt[y] += 1;
                s.insert(make_pair(x, y));
            }
        }
        int ans = summ;
        if (m % 2 == 0) {
            ans = 0;
        } else {
            int f = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (cnt[i] % 2 == 1) {
                    ans = min(ans, a[i]);
                }
            }
            for (auto i: s) {
                if (cnt[i.first] % 2 == 0 && cnt[i.second] % 2 == 0) {
                    ans = min(ans, a[i.first] + a[i.second]);
                }
            }
        }
        cout << ans << "\n";

    }


    return 0;
}
