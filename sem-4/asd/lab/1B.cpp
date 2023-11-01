#include<iostream>
#include <vector>


using namespace std;

class G {

    int n, m;
    vector<vector<int>> a;
    vector<vector<int>> b;

    vector<vector<bool>> aBad;
    vector<vector<bool>> bBad;

    vector<bool> used;
    vector<int> mt;

public:

    void in() {
        cin >> n >> m;
        a.assign(n, {});
        b.assign(m, {});
        aBad.assign(n, vector<bool>(m, false));
        bBad.assign(m, vector<bool>(n, false));
        used.assign(n, false);
        mt.assign(m, -1);


        for (int i = 0; i < n; i++) {
            while (true) {
                int c;
                cin >> c;
                if (c == 0) break;
                aBad[i][--c] = true;
                bBad[c][i] = true;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!aBad[i][j]) {
                    a[i].push_back(j);
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!bBad[i][j]) {
                    b[i].push_back(j);
                }
            }
        }

    }

    void solve() {
        for (int i = 0; i < n; ++i) {
            newIteration();
            kun(i);
        }
    }

    void newIteration() {
        used.assign(n, false);
    }

    auto kun(int node) -> bool {
        if (used[node]) return false;
        used[node] = true;
        for (int to: a[node]) {
            int flag = false;
            if (mt[to] == -1) {
                mt[to] = node;
                return true;
            }
            if (used[mt[to]]) continue;
            if (kun(mt[to])) {
                mt[to] = node;
                flag = true;
            }
            if (flag) return true;
        }
        return false;
    }

    vector<vector<int>> toR;
    vector<int> toL;
    vector<bool> left;

    vector<bool> usedL;
    vector<bool> usedR;

    void init() {
        int ans = 0;
        toR.assign(n, {});
        toL.assign(m, -1);
        left.assign(n, true);
        for (int i = 0; i < m; ++i) {
            toL[i] = mt[i];
            if (mt[i] == -1) continue;
            ans++;
            left[mt[i]] = false;
        }
        for (int i = 0; i < n; i++) {
            for (int to: a[i]) {
                if (mt[to] != i) {
                    toR[i].push_back(to);
                }
            }
        }

        usedL.assign(n, false);
        usedR.assign(m, false);

        for (int i = 0; i < n; i++) {
            if (left[i]) {
                dfs(i);
//                usedL[i] = false;
            }
        }

    }

    void dfs(int v) {
        usedL[v] = true;
        for (int to: toR[v]) {
            usedR[to] = true;
            if (toL[to] != -1) {
//                usedR[to] = true;
                if (!usedL[toL[to]]) {
                    dfs(toL[to]);
                }
            }
        }
    }

    void out() {
        vector<int> ansL;
        vector<int> ansR;
        for (int i = 0; i < n; i++) {
            if (usedL[i]) ansL.push_back(i);
        }
        for (int i = 0; i < m; i++) {
            if (!usedR[i]) ansR.push_back(i);
        }

        cout << ansL.size() + ansR.size() << "\n";
        cout << ansL.size() << " " << ansR.size() << "\n";
        for (int i: ansL) { cout << i + 1 << " "; }
        cout << "\n";
        for (int i: ansR) { cout << i + 1 << " "; }
        cout << "\n";

    }


};

int main() {
    int k;
    cin >> k;
    while (k--) {
        G g;
        g.in();
        g.solve();
        g.init();
        g.out();
        if (k == 0) return 0;
        cout << endl;
    }
}
