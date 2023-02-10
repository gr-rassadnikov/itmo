#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <unordered_set>

using namespace std;

int main() {
    ifstream cin("problem2.in");
    ofstream cout("problem2.out");
    string s;
    cin >> s;
    int n, m, k;
    cin >> n >> m >> k;
    vector<bool> end(n);
    for (int i = 0; i < k; i++) {
        int a;
        cin >> a;
        a--;
        end[a] = true;
    }
    vector<map<char, vector<int>>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        a--;
        b--;
        g[a][c].push_back(b);
    }

    unordered_set<int> Q = {0};
    unordered_set<int> Q_new = {};
    for (auto i: s) {
        for (auto v: Q) {
            for (auto to: g[v][i]) {
                Q_new.insert(to);
            }
//            Q_new.insert(Q_new.end(), g[v][i].begin(), g[v][i].end());
        }
        Q.clear();
        swap(Q, Q_new);
    }
    for (auto i: Q) {
        if (end[i]) {
            cout << "Accepts";
            return 0;
        }
    }
    cout << "Rejects";


    return 0;
}
