#include <iostream>
#include <vector>

using namespace std;
#define ll long long


int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> b(n, 0);
    vector<int> bb(n, 0);
    vector<ll> summ(n, 0);
    vector<ll> summb(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i > 0) {
            b[i] = max(a[i-1] - a[i], 0);
            summ[i] = summ[i - 1] + b[i];
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        if (i < n - 1) {
            bb[i] = max(a[i+1] - a[i], 0);
            summb[i] = summb[i + 1] + bb[i];
        }
    }
    while (m--) {
        int s, t;
        cin >> s >> t;

        if (s < t) {
            cout <<summ[t - 1] - summ[s - 1];
        } else {
            cout << summb[t - 1] - summb[s - 1];
        }
        cout << "\n";
    }


    return 0;
}
