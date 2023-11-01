#include <iostream>
#include <vector>

using namespace std;

int get(vector<int> &s, int ind) {
    if (ind < 0 || ind >= s.size()) return 0;
    return s[ind];
}

struct st {
    int x = 0;
    int y = 0;
    int parent;
    int way;
};

struct use {
    int was = false;
    int min = 1e9;
};

int main() {

    int n;
    cin >> n;
    vector<vector<int>> c(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> c[i + 1][j + 1];
        }
    }
    int m = n;

    vector<st> d(n + 1);
    for (int i = 1; i <= n; ++i) {
        d[0].parent = i;
        int j0 = 0;
        int INF = 1e9;;
        do {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1;
            for (int j = 1; j <= m; ++j)
                if (!used[j]) {
                    int cur = c[i0][j] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur, way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j], j1 = j;
                }
            for (int j = 0; j <= m; ++j)
                if (used[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    vector<int> ans(n + 1);
    for (int j = 1; j <= m; ++j) {
        ans[p[j]] = j;
    }
    int cost = -v[0];
    cout << cost << "\n";
    for (int i = 1; i < n + 1; i++) {
        cout << i << " " << ans[i] << "\n";
    }


}