#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
//    ifstream cin("problem1.in");
//    ofstream cout("problem1.out");
    string s;
    cin >> s;
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> end(k);
    for (int i = 0; i < k; i++) {
        cin >> end[i];
        end[i]--;
    }
    vector<vector<pair<int, char>>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        a--;
        b--;
        g[a].push_back({b, c});
    }

    vector<int> Q = {0};
    vector<int> Q_new = {};
    for (int i = 0; i < s.size(); i++) {
        Q_new.clear();
        for (auto v: Q) {
            for (auto to: g[v]) {
                if (to.second == s[i]) {
                    Q_new.push_back(to.first);
                }
            }
        }
        Q.clear();
        for (auto i: Q_new) {
            Q.push_back(i);
        }
        if (Q.empty()) {
            cout << "Rejects";
            return 0;
        }
    }
    if (std::find(end.begin(), end.end(), Q[0]) != end.end()) {
        cout << "Accepts";
    } else {
        cout << "Rejects";
    }

    return 0;
}
