//
// Created by Grigorii Rassadnikov on 13.02.2023.
//

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define input(a) \
for (int =0; i < a.size(); i++){ \
    cin >> a[i];\
}

#define ll long long

int main() {
    string s;
    cin >> s;
    map<char, ll> d;
    ll l = 1;
    ll r = s.length();

    for (auto i: s) {
        ll res = l * r;
        if (d.contains(i)) {
            d[i] += res;
        } else {
            d[i] = res;
        }
        l++;
        r--;
    }

    for (auto i: d) {
        cout << i.first << ": " << i.second << "\n";
    }


    return 0;
}
