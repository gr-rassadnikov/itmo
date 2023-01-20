//
// Created by Grigorii Rassadnikov on 08.01.2023.
//

#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>

using namespace std;
#define ll long long

int main() {
    ifstream cin("schedule.in");
    ofstream  cout("schedule.out");
    ll n;
    cin >> n;

    vector<pair<ll, ll>> data;

    for (ll i = 0; i < n; ++i) {
        ll d, w;
        cin >> d >> w;
        data.emplace_back(w, d);
    }

    set<ll> used;
    for (ll i = 1; i <= n; i++) {
        used.insert(i);
    }

    std::sort(data.begin(), data.end(), [](auto a, auto b) {
        if (a.first == b.first){
            return a.second<b.second;
        }
        return a.first > b.first;
    });
    ll ans = 0;
//    for (auto i: data) {
//        cout << i.first << " ";
//    }
//    cout << endl;
//    for (auto i: data) {
//        cout << i.second << " ";
//    }
//    cout << endl;
    for (ll i = 0; i < n; i++) {
        auto e = used.lower_bound(data[i].second);
        if (e == used.begin()) {
            if (*e != data[i].second) {
                ans += data[i].first;
            } else {
                used.erase(e);
            }
        } else {
            if (*e != data[i].second) {
                --e;
            }
            used.erase(e);
        }
//        for (auto u: used) {
//            cout << u << " ";
//        }
//        cout << endl;
    }
    cout << ans;

}