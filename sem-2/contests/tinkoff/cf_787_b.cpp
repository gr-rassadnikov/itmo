#include <iostream>
#include <vector>

using namespace std;
#define ll long long


int main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int cnt = 0;
        int cnt0 = 0;
        if(a[n-1]==0){
            cnt0=1;
        }
        for (int i = n - 2; i >= 0; i--) {
            while (a[i] >= a[i + 1]) {
                a[i] = a[i] / 2;
                cnt++;
                if (a[i] == 0) {
                    break;
                }
            }
            if (a[i] == 0) {
                cnt0++;
            }
        }
        if (cnt0 > 1) {
            cout << "-1\n";
        } else {
            cout << cnt <<"\n";
        }
    }


    return 0;
}
