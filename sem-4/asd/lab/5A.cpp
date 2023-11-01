#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;
double pi = 3.1415;

void to(vector<complex<double>> &a) {
    if (1 == a.size()) return;
    int n = a.size();
    int m = n / 2;
    vector<complex<double>> l(m);
    vector<complex<double>> r(m);
    int ind = 0;
    for (int i = 0; i < m; i++) {
        l[ind] = a[2 * i];
        r[ind] = a[2 * i + 1];
        ind++;
    }
    to(l);
    to(r);

    double phi = 2 * pi / n;
    complex<double> w(1);
    complex<double> omega(cos(phi), sin(phi));
    ind = m;
    for (int i = 0; i < m; i++) {
        a[i] = l[i] + w * r[i];
        a[ind] = l[i] - w * r[i];
        w *= omega;
        ind++;
    }
}


void from(vector<complex<double>> &a) {
    if (1 == a.size()) return;
    int n = a.size();
    int m = n / 2;
    vector<complex<double>> l(m);
    vector<complex<double>> r(m);
    int ind = 0;
    for (int i = 0; i < m; i++) {
        l[ind] = a[2 * i];
        r[ind] = a[2 * i + 1];
        ind++;
    }
    from(l);
    from(r);

    double phi = -2 * pi / n;
    complex<double> w(1);
    complex<double> omega(cos(phi), sin(phi));
    ind = n / 2;
    for (int i = 0; i < m; i++) {
        a[i] = (l[i] + w * r[i]) / 2.0;
        a[ind] = (l[i] - w * r[i]) / 2.0;
        w *= omega;
        ind++;
    }

}

vector<int> mul(const vector<int> &a, const vector<int> &b) {
    vector<complex<double>> l(a.begin(), a.end());
    vector<complex<double>> r(b.begin(), b.end());
    int k = 1;
    while (k <= a.size()) {
        k *= 2;
    }
    while (k <= b.size()) {
        k *= 2;
    }
    l.resize(k);
    r.resize(k);

    to(l);
    to(r);
    vector<complex<double>> ans(k);
    for (size_t i = 0; i < k; ++i) {
        ans[i] = l[i] * r[i];
    }
    from(ans);

    vector<int> ansInt(k);
    for (size_t i = 0; i < k; ++i) {
        ansInt[i] = int(ans[i].real() + 0.01);
    }

    int capacity = 0;
    for (size_t i = 0; i < k; ++i) {
        ansInt[i] += capacity;
        capacity = ansInt[i] / 10;
        ansInt[i] %= 10;
    }
    return ansInt;
}

int main() {
    string s, t;
    cin >> s >> t;
    vector<int> a, b;
    int cnt = 0;
    for (char c: s) {
        if (c == '-') {
            cnt++;
            continue;
        }
        a.push_back(c - '0');
    }
    for (char c: t) {
        if (c == '-') {
            cnt++;
            continue;
        }
        b.push_back(c - '0');
    }
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    vector<int> res = mul(a, b);
    std::reverse(res.begin(), res.end());
    bool flag = true;
    if (cnt % 2 == 1) cout << "-";
    for (int i: res) {
        if (i == 0 && flag) continue;
        cout << i;
        flag = false;
    }


}