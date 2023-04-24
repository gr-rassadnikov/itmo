#include <iostream>
#include <vector>

#define ll long long

using namespace std;

int main() {
    int k;
    cin >> k;
    vector<ll> a(k);
    vector<ll> c(k);
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < k; ++i) {
        cin >> c[i];
    }

    vector<ll> q(k + 1, 1);
    vector<ll> p(k, 0);

    for (int i = 1; i < k + 1; ++i) {
        q[i] = -c[i-1];
    }

    for (int i = 0; i < k; ++i) {
        ll res = 0;
        for (int j = 0; j < i; ++j) {
            res += c[j] * a[i - j - 1];
        }
        p[i] = a[i] - res;
    }

    while (!p.empty() && p.back() == 0) {
        p.pop_back();
    }
    while (!q.empty() && q.back() == 0) {
        q.pop_back();
    }

    cout << p.size() - 1 << "\n";
    for (ll v: p) {
        cout << v << " ";
    }
    cout << "\n";


    cout << q.size() - 1 << "\n";
    for (ll v: q) {
        cout << v << " ";
    }
    cout << "\n";

}