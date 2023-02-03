//
// Created by Grigorii Rassadnikov on 25.01.2023.
//

#include <vector>
#include <algorithm>
#include <string>
#include <deque>
#include <map>
#include <set>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include<iostream>

using namespace std;


struct an {
    int value = -1;
    int dp = 10000000;
    int used = 0;
};

int main() {
    int n, k, m;
    cin >> n >> k;
    vector<int> out(k);
    for (int i = 0; i < k; i++) {
        cin >> out[i];
        out[i]--;
    }
    cin >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<an> ans(n);
    int size = 0;
    vector<int> last;
    for (int i = 0; i < k; i++) {
        ans[out[i]].dp = 0;
        ans[out[i]].value = out[i];
        ans[out[i]].used = 1;
        size++;
        last.push_back(out[i]);

    }
    int now = 0;

    while (size < n) {
        vector<int> new_last;
        for (int i: last) {

            for (int j: g[i]) {
                if (ans[j].used == 0) {
                    ans[j].dp = now + 1;
                    ans[j].value = ans[i].value;
                    ans[j].used = 1;
                    size++;
                    new_last.push_back(j);
                } else {
                    if (ans[j].dp == now + 1) {
                        ans[j].value = min(ans[j].value, ans[i].value);
                    }
                }
            }

        }
        last = new_last;

        now++;
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i].dp << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << ans[i].value + 1 << " ";
    }


}