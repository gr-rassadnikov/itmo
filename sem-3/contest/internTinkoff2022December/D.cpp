#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>
#include <map>

using namespace std;

struct Pnt {
    long double x, y;
};

long double pi = 3.14159265358979323;

Pnt pnt(int i, int N) {
    Pnt p;
    p.x = cos(2 * pi * i / N);
    p.y = sin(2 * pi * i / N);
    return p;
}

using Trigon = array<int, 3>;
using Soltri = vector<Trigon>;

struct Solution {
    int N{}, count{};
    long double S = -1;
    Soltri sol;
};

// pair<int,int> - N и количество вершин (отсчет c 0)
map<pair<int, int>, Solution> Rep;

// Площадь треугольника
long double Area(int i, int j, int k, int N) {
    return abs(sin(2 * pi * (j - i) / N) + sin(2 * pi * (k - j) / N) + sin(2 * pi * (i - k) / N)) / 2;
}

// pair<int,int> - начальная вершина и их количество
long double S(pair<int, int> d, Soltri &st, int N) {
    if (d.second < 3) return 0;
    if (auto sl = Rep.find(make_pair(N, d.second)); sl != Rep.end()) {
        for (auto t: sl->second.sol) {
            t[0] += d.first;
            t[1] += d.first;
            t[2] += d.first;
            st.push_back(t);
        }
        return sl->second.S;
    }

    long double maxS = 0;
    Soltri trs;

    int i = d.first, k = d.first + d.second - 1;
    for (int j = max((i + k) / 2, i + 1); j < min((i + k) / 2 + 3, k); ++j) {
        Soltri cur;
        Trigon t{i, j, k};
        cur.push_back(t);
        long double pS = Area(i, j, k, N);
        pair<int, int> a[4];
        a[0] = make_pair(d.first, i - d.first);
        a[1] = make_pair(i + 1, j - i - 1);
        a[2] = make_pair(j + 1, k - j - 1);
        a[3] = make_pair(k + 1, d.second - k - 1);

        pS += S(a[0], cur, N) + S(a[1], cur, N) + S(a[2], cur, N) + S(a[3], cur, N);

        if (pS > maxS) {
            maxS = pS;
            trs = cur;
        }
    }
    Solution sol;
    sol.N = N;
    sol.count = d.second;
    sol.S = maxS;
    for (auto m: trs) {
        st.push_back(m);
        for (int &tg: m) tg -= d.first;
        sol.sol.push_back(m);
    }
    Rep.insert(make_pair(make_pair(N, d.second), sol));

    return maxS;
}

long double Sol(Soltri &st, int N) {
    long double maxS = 0;
    Soltri trs;
    int i = 0;
    for (int j = max(N / 3 - 2, 1); j < max(N / 3 + 2, N); ++j)
        for (int k = max(2 * N / 3 - 2, j + 1); k < max(2 * N / 3 + 2, N); ++k) {
            Soltri cur;
            Trigon t{i, j, k};
            cur.push_back(t);
            long double pS = Area(i, j, k, N);
            pair<int, int> a[4];
            a[0] = make_pair(i + 1, j - i - 1);
            a[1] = make_pair(j + 1, k - j - 1);
            a[2] = make_pair(k + 1, N - k - 1);
            pS += S(a[0], cur, N) + S(a[1], cur, N) + S(a[2], cur, N);
            if (pS > maxS) {
                maxS = pS;
                trs = cur;
            }
        }
    for (auto m: trs) st.push_back(m);
    return maxS;
}

long double S(int N, Soltri &sol) {
    sol.clear();
    return Sol(sol, N);
}

long double Sn(int N) {
    return N * sin(2 * pi / N) / 2;
}

int main(int argc, char *argv[]) {
    cout << fixed << setprecision(6);

    for(int i=0;i<=500;i++) {
        int N = i;
        Soltri sol;
        long double s = S(N, sol);

        long double k = s / Sn(N);
        long double sSmall = (N * cos(pi / N) / sin(pi / N)) / 4;
        cout << k * sSmall << ",\n";
    }

}