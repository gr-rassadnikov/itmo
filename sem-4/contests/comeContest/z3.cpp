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
    set<int> s;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.insert(x);
    }
    vector<int> a;
    for (int i: s) {
        a.push_back(i);
    }
    std::sort(a.begin(), a.end());
    int k;
    cin >> k;
    while (k--) {
        int x;
        cin >> x;
        cout << std::lower_bound(a.begin(), a.end(), x) - a.begin() << "\n";
    }

    return 0;
}
