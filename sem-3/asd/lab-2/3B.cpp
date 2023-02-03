//
// Created by Grigorii Rassadnikov on 26.01.2023.
//

#include <vector>
#include <algorithm>
#include <deque>
#include <map>
#include <set>
#include <cmath>
#include <iomanip>
#include <iostream>
#include<fstream>
#include <queue>
#include <unordered_set>

using namespace std;


struct sufMat {
    string s;
    int n;
    vector<int> p;
    int log_n = -1;
    vector<int> global_c;

    sufMat(string s) :
            s(s),
            n(s.length()),
            p(vector<int>(n, 0)) {
    }

    void radix_sort(vector<pair<pair<int, int>, int>> &a) {
        int n = a.size();
        {
            vector<int> cnt(n, 0);
            for (auto x: a) {
                cnt[x.first.second]++;
            }
            vector<pair<pair<int, int>, int>> aNew(n);
            vector<int> pos(n);
            pos[0] = 0;
            for (int i = 1; i < n; i++) {
                pos[i] = pos[i - 1] + cnt[i - 1];
            }
            for (auto x: a) {
                int i = x.first.second;
                aNew[pos[i]] = x;
                pos[i]++;
            }
            a = aNew;
        }
        {
            vector<int> cnt(n, 0);
            for (auto x: a) {
                cnt[x.first.first]++;
            }
            vector<pair<pair<int, int>, int>> aNew(n);
            vector<int> pos(n);
            pos[0] = 0;
            for (int i = 1; i < n; i++) {
                pos[i] = pos[i - 1] + cnt[i - 1];
            }
            for (auto x: a) {
                int i = x.first.first;
                aNew[pos[i]] = x;
                pos[i]++;
            }
            a = aNew;
        }
    }

    void assignP() {
        vector<pair<char, int>> a(n);
        vector<int> c(n);

        for (int i = 0; i < n; ++i) a[i] = {s[i], i};
        std::sort(a.begin(), a.end());

        for (int i = 0; i < n; ++i) p[i] = a[i].second;
        c[p[0]] = 0;

        for (int i = 1; i < n; ++i) {
            if (a[i].first == a[i - 1].first) {
                c[p[i]] = c[p[i - 1]];
            } else {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }

        int k = 0;
        vector<pair<pair<int, int>, int>> b(n);
        while ((1 << k) < n) {

            for (int i = 0; i < n; ++i) {
                b[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
            }
            radix_sort(b);

            for (int i = 0; i < n; ++i) p[i] = b[i].second;
            c[p[0]] = 0;

            for (int i = 1; i < n; ++i) {
                if (b[i].first == b[i - 1].first) {
                    c[p[i]] = c[p[i - 1]];
                } else {
                    c[p[i]] = c[p[i - 1]] + 1;
                }
            }
            k++;
        }
        global_c = c;
        log_n = k;
    }

    vector<int> lcp() {
        vector<int> cp(n);
        int k = 0;
        for (int i = 0; i < n - 1; ++i) {
            int pi = global_c[i];
            int j = p[pi - 1];
            while (s[i + k] == s[j + k])k++;
            cp[pi] = k;
            k = max(k - 1, 0);
        }
        return cp;
    }


};

int maxPref(string s, string t) {
    for (int i = 0; i < min(s.length(), t.length()); i++) {
        if (s[i] != t[i]) {
            return i;
        }
    }
    return min(s.length(), t.length());
}


int main() {
    string s;
    cin >> s;
    s += char('$');
    sufMat suf = sufMat(s);
    suf.assignP();
    long long ans = 0;
    for (int i = 1; i < s.length(); ++i) {
        ans+=(long long) (suf.p[i] + 1);
    }
//    cout << "\n";
    vector<int> cp = suf.lcp();
    for (int i = 2; i < suf.n; ++i) {
        ans-=(long long)cp[i];
//        cout << maxPref(s.substr(suf.p[i], suf.n - suf.p[i]), s.substr(suf.p[i + 1], suf.n - suf.p[i + 1])) << " ";
    }
    cout << ans;


    return 0;
}




