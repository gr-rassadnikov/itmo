#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
#define ll long long
int cnt = 0;

bool dfs(int v, vector<vector<int>> &g, vector<bool> &used, vector<int> &comp, int to) {
    used[v] = true;
    if (v == to) {
        comp[v] = 0;
        return true;
    }
    for (int i: g[v]) {
        if (!used[i]) {
            if (dfs(i, g, used, comp, to)) {
                comp[v] = 0;
                return true;
            }
        }
    }
    return false;

}

int dfs2(int v, vector<vector<int>> &g, vector<bool> &used, vector<int> &comp, vector<bool> &p) {
    int maxx = -INFINITY;
    used[v] = true;
    for (int i: g[v]) {
        if (!used[i]) {
            maxx = max(maxx, dfs2(i, g, used, comp, p));
        }
    }
    if(comp[v]==0){
        return max(maxx,0);
    }
    if (p[v]) {
        return max(maxx + 1, 0);
    }
    return maxx + 1;
}


int main() {

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cnt = 0;
        string s;
        cin >> s;
        cin >> n >> k;
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        vector<bool> p(n,false);
        for (int i = 0; i < k; i++) {
            int a;
            cin >> a;
            p[a-1]=true;
        }
        vector<vector<int>> g(n);
        for (int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        vector<bool> used(n, false);
        vector<int> comp(n, -1);
        dfs(x, g, used, comp, y);
        int ans=0;
        for (auto i: comp) {
            if (i == 0) {
                ans++;
            }
        }
        ans+= dfs2(x,g,used,comp,p);
        cout << ans << endl;
    }

    return 0;
}
