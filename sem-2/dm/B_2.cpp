#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;


int main() {
    int n;
    char S;
    string s;
    freopen("epsilon.in", "r", stdin);
    freopen("epsilon.out", "w", stdout);
    scanf("%i %c\n", &n, &S);
    vector<vector<char>> g(n);
    vector<bool> is(26, false);
    vector<bool> nott(26, false);
    for (int j = 0; j < n; j++) {
        getline(cin, s);
        char from = s[0];
        g[j].push_back(from);
        if (s.size() < 6) {
            is[from - 'A'] = true;
        } else {
            for (int i = 5; i < s.size(); i++) {
                if ('A' <= s[i] && s[i] <= 'Z') {
                    g[j].push_back(s[i]);
                }else{
                    g[j].push_back('0');
                }
            }
        }
    }
    bool ok = true;
//    cout << n;
    while (ok) {
        ok = false;
        for (int i = 0; i < n; i++) {
            if (!is[g[i][0]-'A']) {
                bool fl = true;
                for (int j = 1; j < g[i].size(); j++) {
                    if(g[i][j]=='0'){
                        fl= false;
                        break;
                    }
                    if (!is[g[i][j]-'A']) {
                        fl = false;
                    }
                }
//                printf("%c %i\n", g[i][0], is[g[i][0]-'A']);
                if (fl && g[i].size() > 1) {
                    ok = true;
                    is[g[i][0]-'A'] = true;
                }
            }
        }
    }
    for (int i = 0; i < 26; i++) {
        if (is[i]) {
//            char c = 'A' + i;
            printf("%c ", 'A' + i);
        }
    }

    return 0;
}

