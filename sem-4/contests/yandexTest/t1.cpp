#include <iostream>
#include <vector>
#include <set>

using namespace std;
#define  ll long long

int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    ll x = 0;
    ll y = 0;
    ll o = -1;
    ll res = 1;
    ll mn = 1e0;
    ll mx = 0;
    ll cnt = 0;
    ll rr = 1;
    for (int i = 0; i < n; ++i) {
        mn = min(mn, a[i]);
        mx = max(mx, a[i]);
        if (a[i] == 0) {
            cnt++;
        } else {
            rr *= a[i];
        }

        res *= a[i];
        if (a[i] > 0) {
            if (x == 0) {
                x = a[i];
            }
            x = min(a[i], x);
        } else if (a[i] < 0) {
            if (y == 0) {
                y = a[i];
            }
            y = max(y, a[i]);
        } else {
            o = 0;
        }
    }
    if (res > 0) {
        if (x == 0) {
            cout << mn;
        } else {
            cout << x;
        }
    } else if (res < 0) {
        if (y == 0) {
            cout << mx;
        } else {
            cout << y;
        }
    } else {
        if (cnt >= 2) {
            cout << 0;
        } else {
            if (rr < 0) {
                cout << y;
            } else {
                cout << 0;
            }
        }
    }

}