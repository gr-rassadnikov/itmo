#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
long double M = -1;

bool sorted(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
    if (((long double) a.first.first - M * (long double) a.first.second) <=
        (long double) b.first.first - M * (long double) b.first.second) {
        return false;
    }
    return true;
}

bool f(int k, vector<int> u, vector<int> w) {
    vector<pair<pair<int, int>, int>> x;
    for (int i = 0; i < u.size(); i++) {
        x.push_back({{u[i], w[i]}, i});
    }

    sort(x.begin(), x.end(), sorted);

    long double s1 = 0;
    long double s2 = 0;
    for (int i = 0; i < k; i++) {
        s1 += (long double) x[i].first.first;
        s2 += (long double) x[i].first.second;
    }
    s2 = s2 * M;
    if (s1 >= s2) {
        return true;
    }
    return false;

}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> w(n);
    vector<int> u(n);
    long double r = 0;
    for (int i = 0; i < n; i++) {
        cin >> u[i];
        r += u[i];
        cin >> w[i];
    }
    long double l = 0;
    while (r > l + 0.0000001) {
        long double m = (r + l) / 2;
        M = m;
        if (f(k, u, w)) {
            l = m;
        } else {
            r = m;
        }
    }
    M = l;
    vector<pair<pair<int, int>, int>> x;
    for (int i = 0; i < u.size(); i++) {
        x.push_back({{u[i], w[i]}, i});
    }
    sort(x.begin(), x.end(), sorted);
    for (int i = 0; i < k; i++) {
        cout << x[i].second + 1 << endl;
    }


}