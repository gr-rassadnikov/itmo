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

bool kuhn(int u, vector<vector<int>> &e, vector<int> &mt, vector<int> &used) {

    used[u] = 1;
    for (int to: e[u]) {
        if (mt[to] == -1) {
            mt[to] = u;
            return true;
        }
        if (used[mt[to]] != 1) {
            if (kuhn(mt[to], e, mt, used)) {
                mt[to] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    ifstream cin("matching.in");
    ofstream  cout("matching.out");
    int n;
    cin >> n;
    vector<pair<int, ll>> w;
    for (int i = 0; i < n; ++i) {
        ll a;
        cin >> a;
        w.push_back({i, a});
    }
    vector<vector<int>> e(n);
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        for (int j = 0; j < m; ++j) {
            int to;
            cin >> to;
            to--;
            e[i].push_back(to);
        }
    }
    std::sort(w.begin(), w.end(), [](auto a, auto b) {
        return a.second > b.second;
    });
    vector<int> mt(n, -1);
    for (int i = 0; i < n; ++i) {
        vector<int> used(n, 0);
        kuhn(w[i].first, e, mt, used);
    }

    vector<int> obratno(n, -1);
    for (int i = 0; i < n; ++i) {
        if (mt[i] >= 0) {
            obratno[mt[i]] = i + 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (obratno[i] == -1) {
            cout << "0 ";
        } else {
            cout << obratno[i] << " ";
        }
    }


}
/*
4
1 3 2 4
4 1 2 3 4
2 1 4
2 1 4
2 1 4
 */