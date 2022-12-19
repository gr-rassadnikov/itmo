//
// Created by Grigorii Rassadnikov on 11.12.2022.
//

#include <iostream>
#include <vector>

using namespace std;


int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        int _min = 1e6;
        int _max = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            _min = min(_min, a[i]);
            _max = max(_max, a[i]);
        }
        long long cnt1 = 0;
        long long cnt2 = 0;
        if (_min != _max) {
            for (int i = 0; i < n; ++i) {
                if (a[i] == _min) {
                    cnt1++;
                } else if (a[i] == _max) {
                    cnt2++;
                }
            }
            cout << 2 * cnt1 * cnt2 << endl;
        }else{
            for (int i = 0; i < n; ++i) {
                if (a[i] == _min) {
                    cnt1++;
                }
            }
            cout << cnt1 * (cnt1-1)<< endl;
        }
    }

    return 0;
}
