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
        int n, m;
        cin >> n >> m;
        vector<int> used(n, -1);
        while (m--) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            int x = min(a, b);
            int y = max(a, b);
            used[y] = max(used[y], x);
        }
        int last = used[0];
        for (int i = 0; i < n; ++i) {
            last = max(last, used[i]);
            used[i] = last;
        }

        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += (i - used[i]);
        }
//        for (int i: used) {
//            cout << i << " ";
//        }
//        cout << endl;
        cout << ans << endl;

    }

    return 0;
}
