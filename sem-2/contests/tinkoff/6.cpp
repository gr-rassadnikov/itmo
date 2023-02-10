#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int get(int l, int r, map<int, int> &sum, map<int, int> &d, int all_sum) {
    int ans = 0;
//    cout << l <<" " << r << endl;
    if (l <= r) {
        for (auto i = d.begin(); i != d.end(); ++i) {
            if (l < i->first && i->first < r) {
                ans += i->second;
            }
        }
        return ans;
    }else{
        for (auto i = d.begin(); i != d.end(); ++i) {
            if (l < i->first || i->first < r) {
                ans += i->second;
            }
        }
        return ans;
    }
    /*
    for (auto i = d.begin(); i != d.end(); ++i) {
        if(i->first>=l){
            l=i->first;
            break;
        }
    }
    for (auto i = d.rbegin(); i != d.rend(); ++i) {
        if(i->first<=r){
            r=i->first;
            break;
        }
    }
    if (r == l) {
        return 0;
    }
    if (r > l) {
        return sum[r] - sum[l] - d[r];
    }
    return all_sum - sum[l] + sum[r] - d[r];
     */
}

int main() {
    int n, h, m, k;
    cin >> n >> h >> m >> k;
    vector<pair<int, int>> in(n);
    map<int, int> d;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        in[i].first = a;
        in[i].second = b;
        if (d.find(b) != d.end()) {
            d[b]++;
        } else {
            d[b] = 1;
        }
    }
    map<int, int> sum;
    int nakop = 0;
    for (auto i = d.begin(); i != d.end(); ++i) {
        nakop += i->second;
        sum[i->first] = nakop;
    }
//    for (auto i = d.begin(); i != d.end(); ++i) {
//        cout << i->first << " " << i->second << " " << sum[i->first] << endl;
//    }
    int min_bad = INT32_MAX;
    int from1 = -1;
    int to1 = -1;
    int from2 = -1;
    int to2 = -1;
    int min_end = INT32_MAX;
    for (auto i = d.begin(); i != d.end(); ++i) {
        int start1 = (i->first) % m;
        int end1 = (start1 + k) % m;
        int start2 = (start1 + m / 2) % m;
        int end2 = (start2 + k) % m;
//        cout << start1 << " " << end1 << " " << start2 << " " << end2 << " " << endl;
        int cnt_bad_train = max(get(start1, end1, sum, d, nakop), get(start2, end2, sum, d, nakop));
//        cout << cnt_bad_train << endl;
        if (cnt_bad_train < min_bad) {
            min_bad = cnt_bad_train;
            from1 = start1;
            to1 = end1;
            from2 = start2;
            to2 = end2;
            min_end = min(end1, end2);
        } else if (cnt_bad_train == min_bad) {
            if (end1 < min_end || end2 < min_end) {
                min_end = min(end1, end2);
                min_bad = cnt_bad_train;
                from1 = start1;
                to1 = end1;
                from2 = start2;
                to2 = end2;
            }
        }

    }
    for (auto i = d.begin(); i != d.end(); ++i) {
        int end1 = (i->first) % m;
        int start1 = (m + end1 - k) % m;
        int start2 = (start1 + m / 2) % m;
        int end2 = (start2 + k) % m;
        //cout << start1 << " " << end1 << " " << start2 << " " << end2 << " " << endl;
        int cnt_bad_train = max(get(start1, end1, sum, d, nakop), get(start2, end2, sum, d, nakop));
//        couut << cnt_bad_train << endl;
        if (cnt_bad_train < min_bad) {
            min_bad = cnt_bad_train;
            from1 = start1;
            to1 = end1;
            from2 = start2;
            to2 = end2;
            min_end = min(end1, end2);
        } else if (cnt_bad_train == min_bad) {
            if (end1 < min_end || end2 < min_end) {
                min_end = min(end1, end2);
                min_bad = cnt_bad_train;
                from1 = start1;
                to1 = end1;
                from2 = start2;
                to2 = end2;
            }
        }
    }
    cout << min_bad << " " << min_end << endl;
    for (int i = 0; i < n; i++) {
        if ((from1 < in[i].second && in[i].second < to1) || (from2 < in[i].second && in[i].second < to2)) {
            cout << i + 1 << " ";
        }
    }
    return 0;
}
/*
 *
7 10 30 3
3 4
5 6
2 0
1 10
2 4
9 0
9 11
 */