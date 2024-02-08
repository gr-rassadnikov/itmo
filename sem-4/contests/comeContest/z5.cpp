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
    int n;
    ll res = 0;
    cin >> n;
    n--;
    ll a;
    cin >> a;
    while (n--) {
        ll b;
        cin >> b;
        res += min(a, b);
        a = b;
    }
    cout << res;
    return 0;
}
