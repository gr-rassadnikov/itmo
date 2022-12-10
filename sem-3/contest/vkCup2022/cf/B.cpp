//
// Created by Grigorii Rassadnikov on 07.12.2022.
//

#include <iostream>
#include <vector>

using namespace std;
#define ll long long

int main() {

    int n;
    cin >> n;
    vector<ll> a(n);
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    ll sumToI = 0;
    vector<bool> used(101, false);

    for (int i = 0; i < n; i++) {
        for (ll p = 0; p <= 100; ++p) {
            ll L1 = a[i] * p;
            ll R1 = a[i] * (p + 1) - 1;
            ll L2 = (sum) * p - 100 * sumToI;
            ll R2 = (sum) * (p + 1) - 100 * sumToI - 1;

//            cout << 1 << " " << L1 << " " << R1 << endl;
//            cout << 2 << " " << L2 << " " << R2 << endl;
//            for (int j = max(L1, L2)*100/a[i]; j < min(R1, R2)*100/a[i]; ++j) {
//                used[j] = true;
//            }
            ll L = max(L1, L2);
            ll R = min(R1,R2);
            if (L<=R) {
                if (L <= (R / 100) * 100 && (R / 100) * 100 <= R){
                    used[p] = true;
                }
            }
        }
        sumToI += a[i];
    }
    for (int i = 0; i <= 100; ++i) {
        if (used[i]) {
            cout << i << "\n";
        }
    }

    return 0;
}
