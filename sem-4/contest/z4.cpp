//
// Created by Grigorii Rassadnikov on 13.02.2023.
//

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

#define input(a) \
for (int =0; i < a.size(); i++){ \
    cin >> a[i];\
}

#define ll long long

int main() {
    int n;
    cin >> n;
    int k;
    cin >> k;
    int x, y;
    cin >> x >> y;

    int p1 = (x - 1) * 2 + y - k;
    int p2 = (x - 1) * 2 + y + k;
    int e1 = (p1 + 1) / 2;
    int e2 = (p2 + 1) / 2;

    if (p2 > n || abs(x - e2) > abs(x - e1)) {
        if (p1 > 0) {
            cout << e1 << " " << 2 - p1 % 2;
        } else {
            cout << -1;
        }
    } else if (p2 <= n) {
        cout << e2 << " " << 2 - p2 % 2;
    }

//    2int q, t;
//    if (2 * (x - 1) + y + k - 1 >= n) {
//        q = -1;
//        t = -1;
//    } else {
//        q = (2 * (x - 1) + y + k - 1) / 2 + 1;
//        t = (2 * (x - 1) + y + k - 1) % 2 + 1;
//    }
////    cout << q << " " << t << "\n";
//    int u, v;
//    if (2 * (x - 1) + y - k <= 0) {
//        u = -1;
//        v = -1;
//    } else {
//        u = (2 * (x - 1) + y - k - 1) / 2 + 1;
//        v = (2 * (x - 1) + y - k - 1) / 2 + 1;
//    }
////    cout << u << " " << v;
//
//    if (q == -1) {
//        if (u == -1) {
//            cout << -1;
//        } else {
//            cout << u << " " << v;
//        }
//    } else {
//        if (u == -1) {
//            cout << q << " " << t;
//        } else {
//            if (q - x <= x - u) {
//                cout << q << " " << t;
//            } else {
//                cout << u << " " << v;
//            }
//        }
//    }

    return 0;
}
