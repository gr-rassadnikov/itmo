//
// Created by Grigorii Rassadnikov on 07.12.2022.
//

#include <iostream>
#include <vector>

using namespace std;

void upd(int &ans, int l, int r) {
    ans = max(ans, r - l + 1);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int L1 = -1;
        int L2 = -1;
        int R1 = -1;
        int R2 = -1;
        int ans = 0;
        for (int i = 0; i < n;) {
            upd(ans, L1, R1);
            upd(ans, L2, R2);
            int x = a[i];
            int cnt = 0;
            while (i < n && a[i] == x) {
                i++;
                cnt++;
            }
//            cout << "--" << x << " " << cnt << "\n";
//            cout << L1 << R1 << endl;
//            cout << L2 << R2 << endl;
            if (cnt > 1) {
                if (R1 >= x - 1) {
                    R1 = x + 1;
                }
                if (R2 >= x - 1) {
                    R2 = x + 1;
                }
            }
            if (cnt == 1) {
                if (R1 == x) {
                    R1++;
                } else if (R1 == x - 1) {
                    R1++;
                }
                if (R2 == x) {
                    R2++;
                } else if (R2 == x - 1) {
                    upd(ans, L2, R2 + 1);
                }
            }

            upd(ans, L1, R1);
            upd(ans, L2, R2);

            if (R1 < x) {
                L1 = x;
                if (R2 >= x - 1) {
                    L1 = L2;
                }
                if (cnt > 1) {
                    R1 = x + 1;
                } else {
                    R1 = x;
                }
            }

            if (R2 < x) {
                R2 = x + 1;
                if (cnt > 1) {
                    L2 = x;
                } else {
                    L2 = x + 1;
                }
            }
            upd(ans, L1, R1);
            upd(ans, L2, R2);
//            cout << "++" << x << " " << cnt << "\n";
//            cout << L1 << R1 << endl;
//            cout << L2 << R2 << endl;
        }
        upd(ans, L1, R1);
        upd(ans, L2, R2);
        cout << ans << "\n";
    }

    return 0;
}
