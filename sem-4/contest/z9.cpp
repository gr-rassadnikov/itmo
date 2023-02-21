//
// Created by Grigorii Rassadnikov on 13.02.2023.
//

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define input(a) \
for (int =0; i < a.size(); i++){ \
    cin >> a[i];\
}

#define ll long long

int main() {

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<ll>> a(n, vector<ll>(m, 0));
    vector<vector<ll>> sum(n, vector<ll>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            if (i == 0 && j == 0) {
                sum[i][i] = a[i][j];
            } else if (i == 0) {
                sum[i][j] = sum[i][j - 1] + a[i][j];
            } else if (j == 0) {
                sum[i][j] = sum[i - 1][j] + a[i][j];
            } else {
                sum[i][j] = -sum[i - 1][j - 1] + sum[i - 1][j] + sum[i][j - 1] + a[i][j];
            }
        }
    }
//    for (auto i: sum) {
//        for (auto j: i) {
//            cout << j << " ";
//        }
//        cout << "\n";
//    }
    while (k--) {
        int x1, x2;
        int y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--;
        x2--;
        y1--;
        y2--;
        if (x1 == 0 && y1 == 0) {
            cout << sum[x2][y2] << "\n";
        } else if (x1 == 0) {
            cout << sum[x2][y2] - sum[x2][y1 - 1] + sum[x1][y1] << "\n";
        } else if (y1 == 0) {
            cout << sum[x2][y2] - sum[x1 - 1][y2] + sum[x1][y1] << "\n";
        } else {
            cout << sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1] << "\n";
        }
    }

    return 0;
}
