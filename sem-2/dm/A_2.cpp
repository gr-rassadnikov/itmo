#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <unordered_set>

using namespace std;

bool my(string &s, vector<map<char, vector<int>>> &g, vector<bool> &end, int start, int index) {
    if (index >= s.size() - 1) {
        if (std::find(g[start][s[index]].begin(), g[start][s[index]].end(), 26) != g[start][s[index]].end()) {
            return true;
        }
        return false;
    }
    if (start == 26) {
        return false;
    }
    if (g[start][s[index]].empty()) {
        return false;
    }
    bool ans = false;
    for (int i: g[start][s[index]]) {
        ans = ans || my(s, g, end, i, index + 1);
    }
    return ans;
}


int main() {
    ifstream cin("automaton.in");
    ofstream cout("automaton.out");
    int n;
    char S;
    cin >> n >> S;
    vector<map<char, vector<int>>> g(27);
    vector<bool> end(27, false);
    string s;
    getline(cin, s);
    for (int i = 0; i < n; i++) {
        getline(cin, s);
        int from = s[0] - 'A';
        int to;
        if (s.size() == 7) {
            to = s[6] - 'A';
        } else {
            to = 26;
        }
        char rebro = s[5];
        g[from][rebro].push_back(to);
        end[to] = true;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        if (my(s, g, end, S - 'A',0)) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
    }
    return 0;
}