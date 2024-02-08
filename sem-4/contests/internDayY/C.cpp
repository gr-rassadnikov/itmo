#include <iostream>
#include<vector>
#include <map>
#include <string>
#include <set>
#include <algorithm>

using namespace std;
#define double long double


void get_per(int m, int k, vector<int> per, vector<vector<int>> &data) {
//    cout << m << k << "\n";
    if (m == 0 && k == 0) {
        data.push_back(per);
        return;
    }
    if (m == 0) {
        return;
    }
    per.push_back(0);
    get_per(m - 1, k, per, data);
    per.pop_back();
    if (k > 0) {
        per.push_back(1);
        get_per(m - 1, k - 1, per, data);
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> cost(n);
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
    }
    vector<set<int>> d(n);
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        while (c--) {
            int h;
            cin >> h;
            d[i].insert(h - 1);
        }
    }

    vector<int> discount(m);
    vector<double> mn(m);
    for (int i = 0; i < m; i++) {
        cin >> discount[i];
        mn[i] = ((double) (100 - discount[i])) / 100.0;
    }

    vector<int> st_per;
    for (int i = 0; i < m; i++) {
        st_per.push_back(i);
    }

    double ans = 1e9;
    vector<int> ans_per;
    int ans_t = 0;

    vector<vector<int>> data;
    get_per(m, k, {}, data);
//    cout << data.size();

    for (auto p: data) {
//        for (int i = 0; i < p.size(); i++) {
//            cout << p[i] << " ";
//        }
//        cout << "\n";

        vector<int> per;
        for (int i = 0; i < p.size(); ++i) {
            if (p[i]) {
                per.push_back(i);
            }
        }

        vector<double> coef(n, 1);
        int loc_t = 0;
        for (int i = 0; i < k; i++) {
            int index = per[i];
            double mnoj = mn[index];
            bool flag = false;
            for (int j = 0; j < n; j++) {
                if (d[j].contains(index)) {
                    coef[j] *= mnoj;
                    flag = true;
                }
            }
            if (!flag) {
                break;
            }
            loc_t++;
        }


        double loc_min = 0;
        for (int j = 0; j < n; j++) {
            loc_min += coef[j] * cost[j];
        }
        if (loc_min < ans) {

            ans = loc_min;
            ans_per = per;
            ans_t = loc_t;
        }
    }

    cout << ans_t << "\n";
    for (
            int i = 0;
            i < ans_t;
            i++) {
        cout << ans_per[i] + 1 << " ";
    }


}


