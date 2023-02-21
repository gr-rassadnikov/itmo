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
    string s;

    map<char, int> d;
    while (cin >> s) {
//        if(s=="q") break;
    for (auto i: s) {
        if (i != ' ') {

            if (d.contains(i)) {
                d[i]++;
            } else {
                d[i] = 1;
            }
        }
    }
    }
    int m = 0;
    for (auto i: d) {
        m = max(m, i.second);
    }
    int w = m;
    while (w--) {
        for (auto &i: d) {
            if (i.second == m) {
                cout << "#";
            } else {
                cout << " ";
                i.second++;
            }
        }
        cout << "\n";
    }
    for (auto i: d) {
        cout << i.first;
    }


    return 0;
}
