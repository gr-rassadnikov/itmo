#include <iostream>
#include <vector>


using namespace std;


int main() {
    ios_base:: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    int q = 0;
    vector<int> size(n);
    vector<vector<int>> items(n);
    vector<vector<int>> d(n);
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        if (m == 0) {
            q++;
            size[i] = 0;
        } else {
            size[i] = m;
            for (int j = 0; j < m; j++) {
                items[i].push_back(0);
                cin >> items[i][j];
            }
            int k = 1;
            for (int o = 0; o < m; o++) {
                k = k * 2;
            }
            for (int j = 0; j < k; j++) {
                d[i].push_back(0);
                cin >> d[i][j];
            }
        }
    }
    int kq = 1;
    for (int o = 0; o < q; o++) {
        kq = kq * 2;
    }
    vector<pair<int, int>> qqq;
    int indqqq = 0;
    int maxx = 0;
    qqq.push_back({n - 1, 0});
    vector <int> use(n,0);

    while (true) {
        pair<int, int> x = qqq[indqqq];
        use[x.first]=1;
        maxx = x.second;
        for (int h: items[x.first]) {
            qqq.push_back({h - 1, x.second + 1});
        }
        indqqq++;
        if (indqqq == qqq.size()) {
            break;
        }
    }
    cout << maxx << endl;
    for (int i = 0; i < kq; i++) {
        int x = i;
        vector<int> y(q, 0);
        for (int j = 0; j < q; j++) {
            y[q - j - 1] = x % 2;
            x = x / 2;
        }
        vector<int> ans(n);
        int ind = 0;
        for (int j = 0; j < n; j++) {
            if (size[j] == 0) {
                ans[j] = y[ind++];
            }
            if (size[j] > 0) {
                vector<int> p(items[j].size());
                int indd=0;
                for (int f=0;f<items[j].size();f++) {
                    p[indd] = ans[items[j][f]-1];
                    indd++;
                }
                int st = 1;
                int su = 0;
                for (int c = p.size() - 1; c >= 0; c--) {
                    su += p[c] * st;
                    st = st * 2;
                }
                ans[j] = d[j][su];
            }
        }
        cout << ans[n - 1];


    }
    return 0;
}
