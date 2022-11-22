
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;
    vector<set<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].insert(b);
        g[b].insert(a);
    }

    set<int> leafs;
    vector<bool> used(n, false);
    for (int i = 0; i < n; i++) {
        if (g[i].size() == 1) {
            leafs.insert(i);
        }
    }

    vector<int> ans;

    for (int i = 0; i < n - 2; i++) {
        int v = *leafs.begin();
        int j = *g[v].begin();
        g[j].erase(v);
        g[v].erase(j);
        ans.push_back(j);
        if (g[j].size() == 1) {
            leafs.insert(j);
        }
        leafs.erase(v);
    }


    for (int i: ans) {
        cout << i + 1 << " ";
    }

}