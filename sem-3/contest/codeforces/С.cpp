//
// Created by Grigorii Rassadnikov on 11.12.2022.
//

#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;


int main() {

    int to = 31622 + 1;
    vector<bool> g(to + 1, true);
    g[0] = false;
    g[1] = false;
    vector<int> promises;
    for (int i = 2; i <= to; i++) {
        if (g[i]) {
            promises.push_back(i);
            int d = i + i;
            while (d <= to) {
                g[d] = false;
                d += i;
            }
        }
    }
//    for (int i = 0; i < 5; ++i) {
//        cout << promises[i];
//    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        bool res = false;
        unordered_set<int> w;
        unordered_map<int, int> ww;

        bool was = false;

        for (int i = 0; i < n; ++i) {
            for (int p: promises) {
                if (a[i] % p == 0) {
                    if (w.contains(a[i]) ) {
                        if (ww[a[i]] != i) {
//                            cout << p << a[i] / p << endl;
                            res = true;
                        }
                        break;
                    }
                    if ( w.contains(p)) {
                        if (ww[p] != i) {
//                            cout << p << a[i] / p << endl;
                            res = true;
                        }
                        break;
                    }
                    if (w.contains(a[i] / p)) {
                        if (ww[a[i]/p] != i) {
//                            cout << p << a[i] / p << endl;
                            res = true;
                        }
                        break;
                    }
                    w.insert(p);
                    ww[p] = i;
                    if (p != a[i]) {
                        w.insert(a[i] / p);
                        ww[a[i] / p] = i;
                    }

                }
            }
            if (res) {
                break;
            }
        }


        set<int> s;
        for (int i: a) {
            if (res) {
                break;
            }
            if (i != 1 && s.contains(i)) {
                res = true;
                break;
            }
            s.insert(i);
        }

        if (res) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }

    }

    return 0;
}
