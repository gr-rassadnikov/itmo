#include <iostream>
#include <vector>
#include <set>

using namespace std;
#define ll long long

int main() {
    int n;
    cin >> n;
    vector<pair<ll, ll>> a(n);
    set<pair<ll, ll>> has;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        has.insert(a[i]);
    }

    ll mx = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j)continue;

            ll x1 = a[i].first;
            ll y1 = a[i].second;

            ll x4 = a[j].first;
            ll y4 = a[j].second;

            pair<ll, ll> p2 = {x4, y1};
            pair<ll, ll> p3 = {x1, y4};
            if (has.contains(p2) && has.contains(p3)) {
                mx = max(mx, abs(x4 - x1) * abs(y4 - y1));
            }
        }
    }
    cout << mx;

}