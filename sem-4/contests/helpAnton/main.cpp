#include <vector>
#include <algorithm>
#include <string>
#include <deque>
#include <map>
#include <set>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <iostream>

using namespace std;

struct rebro {
    int e, n;
};

vector<bool> used;
vector<vector<rebro>> G;
vector<int> up;
vector<int> num;
vector<int> edges;

int t = 0;

bool dfs(int v, int p, int n) {
    used[v] = true;
    num[v] = t++;
    up[v] = num[v];

    bool was = v == n;

    for (auto to: G[v]) {
        if (!used[to.e]) {
            was = was || dfs(to.e, to.n, n);
        }

        if (to.n != p) {
            up[v] = min(up[v], up[to.e]);
        }
    }

    if (up[v] == num[v] && p != -1 && was) {
        edges.push_back(p);

    }
    return was;
}

int main() {
    int n, m;

    cin >> n >> m;
    G.resize(n);
    used.resize(n);
    num.assign(n, 1e9);
    up.resize(n, 1e9);

    int a, b;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        --a, --b;
        G[a].push_back({b, i});
        G[b].push_back({a, i});
    }


    dfs(0, -1, n - 1);


    cout << edges.size() << endl;
    sort(edges.begin(), edges.end());
    for (auto i: edges) {
        cout << i + 1 << " ";
    }
    return 0;
}