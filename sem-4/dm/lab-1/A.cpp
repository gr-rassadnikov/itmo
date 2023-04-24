#include <iostream>
#include <vector>

using namespace std;
#define t long long

struct polynom {
public:
    int deg;
    vector<t> a;
    const long long mod = 998244353;

    polynom(int deg) : deg(deg) {};

    polynom(int deg, vector<t> &a) : deg(deg), a(a) {};

    void input() {
        for (int i = 0; i < deg + 1; ++i) {
            t c;
            cin >> c;
            a.push_back(c);
        }
    }

    t get(int i) const {
        return i > deg ? (t) 0 : a[i];
    }

    polynom sum(const polynom &q) const {
        vector<t> result;
        for (int i = 0; i <= max(deg, q.deg); ++i) {
            result.push_back((get(i) + q.get(i)) % mod);
        }
        return polynom(result.size() - 1, result);
    }

    polynom multiply(const polynom &q) const {
        vector<t> result(deg + q.deg + 1, 0);
        for (int i = 0; i <= deg + q.deg; ++i) {
            for (int j = 0; j <= i; ++j) {
                result[i] = (result[i] + (get(j) * q.get(i - j)) % mod) % mod;
            }
        }
        return polynom(result.size() - 1, result);
    }

    polynom divide(const polynom &q) const {
        int to = 1000;
        vector<t> result(to, 0);
        for (int i = 0; i < to; ++i) {
            result[i] = get(i);
            for (int j = 0; j < i; ++j) {
                result[i] = (mod + result[i] - (result[j] * q.get(i - j)) % mod) % mod;
            }
            result[i] = result[i] / q.get(0);
        }
        return polynom(to-1, result);
    }

    void canonic() {
        while (!a.empty() && a.back() == (t) 0) {
            a.pop_back();
        }
        deg = max(0, (int) a.size() - 1);
    }

    void print() {
        for (int i = 0; i < deg + 1; ++i) {
            cout << a[i] << " ";
        }
        cout << "\n";
    }

};

int main() {

    int n, m;
    cin >> n >> m;
    polynom p(n), q(m);
    p.input();
    q.input();


    polynom summ = p.sum(q);
    summ.canonic();
    cout << summ.deg << "\n";
    summ.print();

    polynom mul = p.multiply(q);
    mul.canonic();
    cout << mul.deg << "\n";
    mul.print();

    polynom div = p.divide(q);
    div.print();

}