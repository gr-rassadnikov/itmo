//
// Created by Grigorii Rassadnikov on 15.01.2023.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> d(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            d[a[i]]++;
        }
        std::sort(a.begin(), a.end());
        int ans = 0;
        int sum = 0;
        int last = -1;
        for (int i = 0; i < n; ++i) {
            sum += d[i];
            if (d[i] > 0) {
                if (last >= i) {
                    ans--;
                    last = -1;
                }
            }
            if ((d[i] > 0) && sum - 1 >= i) {
                ans += 1;
                last = sum;
//                if (d[i + 1] != 0 && sum >= i + 1) {
//                    ans--;
//                }
            }
//            sum += d[i];
        }
        if (d[0] == 0) {
            ans++;
        }
        cout << ans << "\n";
    }

    return 0;
}
