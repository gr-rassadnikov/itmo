#include <iostream>
#include <vector>


using namespace std;
#define t long long

struct polynom {
public:
    int deg;
    vector<t> a;
    t mod = 998244353;

    polynom(int deg) : deg(deg) {};

    polynom(int deg, vector<t> &a) : deg(deg), a(a) {};

    polynom(vector<t> a) : deg(a.size() - 1), a(a) {};

    void input() {
        for (int i = 0; i < deg + 1; ++i) {
            t c;
            cin >> c;
            a.push_back(c);
        }
    }

    t get(int i) const {
        return i > deg ? (t) 0 : a[i] % mod;
    }

    polynom sum(const polynom &q) const {
        vector<t> result;
        for (int i = 0; i <= max(deg, q.deg); ++i) {
            result.push_back((get(i) + q.get(i)) % mod);
        }
        return polynom(result.size() - 1, result);
    }

    polynom multiply(polynom &q, t m) {
        vector<t> result(min((t) deg + q.deg + 1, m), 0);
        for (t i = 0; i < result.size(); ++i) {
            for (t j = 0; j <= i; ++j) {
                result[i] = (result[i] + (get(j) * q.get(i - j)) % mod) % mod;
            }
        }
        return polynom(result.size() - 1, result);
    }


    void canonic() {
        while (!a.empty() && a.back() == (t) 0) {
            a.pop_back();
        }
        deg = max(0, (int) a.size() - 1);
    }


    polynom sqtr(t m) {
        vector<t> result(m, 0);
        result[0] = 1;
        polynom tmp(vector<t>(1, 1));
        for (t i = 1; i < m; ++i) {
            tmp = tmp.multiply(*this, m);
            tmp.canonic();

            t c_sqrt = (get_c_sqrt(i) + mod) % mod;
            for (t j = 0; j < m; ++j) {
                result[i] = (result[i] + (c_sqrt * tmp.get(j)) % mod) % mod;
            }
        }
        return polynom(result);
    }

    polynom exp(t m) {
        vector<t> result(m, 0);
        result[0] = 1;
        polynom tmp(vector<t>(1, 1));
        t c_exp = 1;
        for (t i = 1; i < m; ++i) {
            tmp = tmp.multiply(*this, m);
            tmp.canonic();

            c_exp = (c_exp * i) % mod;
            for (t j = 0; j < m; ++j) {
                result[i] = (result[i] + (pow(c_exp, mod - 2) % mod * tmp.get(j)) % mod) % mod;
            }
        }
        return polynom(result);
    }

    polynom ln(t m) {
        vector<t> result(m, 0);
        result[0] = 0;
        polynom tmp(vector<t>(1, 1));
        t c_ln = mod - 1;
        for (t i = 1; i < m; ++i) {
            tmp = tmp.multiply(*this, m);
            tmp.canonic();

            c_ln = (-1 * c_ln + mod) % mod;
            for (t j = 0; j < m; ++j) {
                result[i] = (result[i] + ((c_ln * pow(i, mod - 2) % mod) * tmp.get(j)) % mod) % mod;
            }
        }
        return polynom(result);
    }

    t get_c_sqrt(t to) {
        t p = 1, q = 1;
        for (t i = 0; i < to; ++i) {
            p = (p * (1 - 2 * i + mod)) % mod;
            q = (q * (((i + 1) * 2) % mod)) % mod;
        }
        return (p * pow(q, mod - 2)) % mod;
    }

    t pow(t c, t to) {
        if (to % 2 == 1) {
            if (to == 1) {
                return c;
            }
            return (c * pow(c, to - 1)) % mod;
        } else {
            t kv = pow(c, to / 2) % mod;
            return (kv * kv) % mod;
        }
    }

    void print() {
        for (auto i: a) {
            cout << i << " ";
        }
        cout << "\n";
    }

};

int main() {

    int n, m;
    cin >> n >> m;
    polynom p(n);
    p.input();
    p.sqtr(m).print();
    p.exp(m).print();
    p.ln(m).print();

}