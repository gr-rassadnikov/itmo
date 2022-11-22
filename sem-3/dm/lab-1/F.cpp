//
// Created by Grigorii Rassadnikov on 02.11.2022.
//

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> p(n - 2);
    vector<pair<int, int>> g;
    vector<int> cnt(n, 0);
    for (int i = 0; i < n - 2; i++) {
        cin >> p[i];
        p[i]--;
        cnt[p[i]]++;
    }

    set<int> V;
    set<int> null;
    for (int i = 0; i < n; i++) {
        if (cnt[i] == 0) {
            null.insert(i);
        }
    }
    for (int i = 0; i < n; i++) {
        V.insert(i);
    }
    reverse(p.begin(), p.end());

    while (!p.empty()) {
        int u = p.back();
        p.pop_back();
        int v = *null.begin();
        g.push_back({u, v});
        null.erase(v);
        cnt[u]--;
        if (cnt[u] == 0) {
            null.insert(u);
        }
    }
    int u = *null.begin();
    null.erase(u);
    g.push_back({u, *null.begin()});
    for (auto i: g) {
        cout << i.first + 1 << " " << i.second + 1 << "\n";
    }

}