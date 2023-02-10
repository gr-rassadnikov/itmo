#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <deque>
#include <map>
#include <set>

using namespace std;

int main() {
    ifstream cin("equivalence.in");
    ofstream cout("equivalence.out");
//    int mod = 1e9 + 7;
    int n, m, k;
    cin >> n >> m >> k;
    vector<bool> end1(n + 1, false);
    for (int i = 0; i < k; i++) {
        int a;
        cin >> a;
        a--;
        end1[a] = true;
    }
    vector<map<char, int>> g1(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        a--;
        b--;
        g1[a][c] = b;
    }
    for (int i = 0; i <= n; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            if (g1[i].find(c) == g1[i].end()) {
                g1[i][c] = n;
            }
        }
    }


    cin >> n >> m >> k;
    vector<bool> end2(n + 1, false);
    for (int i = 0; i < k; i++) {
        int a;
        cin >> a;
        a--;
        end2[a] = true;
    }
    vector<map<char, int>> g2(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        a--;
        b--;
        g2[a][c] = b;
    }
    for (int i = 0; i <= n; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            if (g2[i].find(c) == g2[i].end()) {
                g2[i][c] = n;
            }
        }
    }
//    for (auto &i: g1) {
//        std::sort(i.begin(), i.end());
//    }
//    for (auto &i: g2) {
//        std::sort(i.begin(), i.end());
//    }

    deque<pair<int, int>> Q = {{0, 0}};
    set<pair<int, int>> used;
    used.insert({0, 0});

    while (!Q.empty()) {
        int v1 = Q.front().first;
        int v2 = Q.front().second;

        if (end1[v1] != end2[v2]) {
            cout << "NO";
            return 0;
        }
        for (char c = 'a'; c <= 'z'; c++) {
            pair<int, int> r = {g1[v1][c], g2[v2][c]};
            if (used.find(r) == used.end()) {
                if (end1[r.first] != end2[r.second]) {
                    cout << "NO";
                    return 0;
                }
                Q.push_back(r);
                used.insert(r);
            }
        }
        Q.pop_front();

    }
    cout << "YES";


    return 0;
}
