#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


using namespace std;

long long pImpl(long long left, long long right, vector<long long> &points, long long s, long long n,
                vector<pair<long long, long long >> &a) {
    long long l_cnt = 0;
    long long r_cnt = 0;
    long long add = 0;
    vector<long long> bad;
    for (auto &i: a) {
        if (i.second < left) {
            add += i.first;
            l_cnt++;
        } else if (i.first > right) {
            add += i.first;
            r_cnt++;
        } else {
            bad.push_back(i.first);
        }
    }
    sort(bad.begin(), bad.end());

    if (l_cnt > n / 2 || r_cnt > n / 2) {
        return -1;
    }
    long long b = n / 2 - l_cnt;
    long long aa = n / 2 + 1 - r_cnt;
    for (int i = 0; i < n; i++) {
        if (i == b) {
            break;
        }
        add += bad[i];
    }
    long long mediana = min((s - add > 0 ? s - add : 0) / (aa), right);
    add += mediana * aa;
    if (add > s || mediana < left || mediana > right) {
        return -1;
    }
    return mediana;
}

void propogate(long long &res, long long index, vector<long long> &points, long long s, long long n,
               vector<pair<long long, long long >> &a) {
    res = max(res, pImpl(points[index], points[index], points, s, n, a));
}

void propogateHard(long long &res, long long index, vector<long long> &points,
                   long long s, long long n, vector<pair<long long, long long >> &a) {
    res = max(res, pImpl(points[index], points[index + 1], points, s, n, a));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long long n, s;
    cin >> n >> s;
    vector<pair<long long, long long>> a(n);
    set<long long> sep;
    vector<long long> points;
    for (long long i = 0; i < n; ++i) {
        long long l, r;
        cin >> l >> r;
        a[i] = make_pair(l, r);
        sep.insert(l);
        sep.insert(r);
    }
    for (auto i: sep) {
        points.push_back(i);
    }
    long long points_len = points.size();
    long long point_len_divide_2 = points_len / 2;
    long long index = point_len_divide_2;
    long long res = -1;


    if (index > 1) {
        propogate(res, index - 1, points, s, n, a);
        propogateHard(res, index - 1, points, s, n, a);
    }
    if (index < n) {
        propogate(res, index + 1, points, s, n, a);
        propogateHard(res, index, points, s, n, a);
    }
    if (0 < index && index < n + 1) {
        propogate(res, index, points, s, n, a);
    }
    if (0 < index && index < n) {
        propogateHard(res, index, points, s, n, a);
    }
    cout << res;
}
