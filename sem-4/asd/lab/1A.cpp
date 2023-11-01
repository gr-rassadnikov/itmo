#include<iostream>
#include <vector>


using namespace std;

class G {

    int n, m;
    vector<vector<int>> a;
    vector<vector<int>> b;

    vector<bool> used;
    vector<int> mt;

public:

    void in() {
        cin >> n >> m;
        a.assign(n, {});
        b.assign(m, {});
        used.assign(n, false);
        mt.assign(m, -1);

        for (int i = 0; i < n; i++) {
            while (true) {
                int c;
                cin >> c;
                if (c == 0) break;
                a[i].push_back(--c);
                b[c].push_back(i);
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


    void out() {
        int ans = 0;
        for (int i = 0; i < m; ++i) {
            if (mt[i] == -1) continue;
            ans++;
        }
        cout << ans << "\n";
        for (int i = 0; i < m; ++i) {
            if (mt[i] == -1) continue;
            cout << mt[i] + 1 << " " << i + 1 << "\n";
        }
    }

};

int main() {
    G g;
    g.in();
    g.solve();
    g.out();
}
