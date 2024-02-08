#include <iostream>
#include <vector>
#include <map>

using namespace std;

void f(vector<vector<vector<bool>>> &d, int to, int f1, int f2, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            d[to][i].push_back(d[f1][i][j] && d[f2][i][j]);
        }
    }
}

void fHard(vector<vector<vector<bool>>> &d, int to, int f1, int f2, int f3, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            d[to][i].push_back(d[f1][i][j] && d[f2][i][j] && d[f3][i][j]);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<vector<bool>>> d(7, vector<vector<bool>>(n));
    map<char, int> index = {
            {'B', 0},
            {'R', 1},
            {'Y', 2},
            {'P', 3},
            {'G', 4},
            {'O', 5},
            {'V', 6}
    };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; k++) {
                char c;
                cin >> c;
                if (c == '1') {
                    d[i][j].push_back(true);
                } else {
                    d[i][j].push_back(false);
                }
            }
        }
    }

    f(d, 3, 0, 1, n, m);
    f(d, 4, 0, 2, n, m);
    f(d, 5, 1, 2, n, m);
    fHard(d, 6, 0, 1, 2, n, m);

//    for (int h = 0; h < 7; ++h) {
//        cout << h << ":\n";
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < n; ++j) {
//                cout << d[h][i][j];
//            }
//            cout << "\n";
//        }
//    }
    vector<string> tv(n);
    for (int i = 0; i < n; ++i) {
        cin >> tv[i];
    }


    for (int i = 0; i < n; ++i) {
        int j = -1;
        for (char c: tv[i]) {
            j++;
            if (c == 'D') {
                continue;
            }
            int ind = index[c];
            if (!d[ind][i][j]) {
                cout << "NO";
                return 0;
            }
        }
    }

    cout << "YES";
}