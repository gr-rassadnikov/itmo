#include <iostream>
#include <vector>

using namespace std;
#define t long long

const long long mod = 104'857'601;

struct polynom {
public:
    int deg;
    vector<t> a;

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

    polynom multiply(const polynom &q) const {
        vector<t> result(deg + q.deg + 1, 0);
        for (int i = 0; i <= deg + q.deg; ++i) {
            for (int j = 0; j <= i; ++j) {
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

    void print() {
        for (int i = 0; i < deg + 1; ++i) {
            cout << a[i] << " ";
        }
        cout << "\n";
    }

    static t get(int i, vector<t> &f) {
        return i >= f.size() ? (t) 0 : f[i];
    }

    static vector<t> mul(vector<t> &p, vector<t> &q) {
        vector<t> result(p.size() + q.size() - 1, 0);
        for (int i = 0; i < result.size(); ++i) {
            for (int j = 0; j <= i; ++j) {
                result[i] = (result[i] + (get(j, p) * get(i - j, q)) % mod) % mod;
            }
        }
        return result;
    }

    static void get_nth(int n, int k, vector<t> &a, vector<t> &q) {
        while (n >= k) {
            for (int i = k; i < 2 * k; ++i) {
                t res = 0;
                for (int j = 1; j <= k; ++j) {
                    res = (res + (mod - q[j] * a[i - j]) % mod) % mod;
                }
                a[i] = res;
            }

            vector<t> q_minus_t(q);
            for (int i = 0; i < k + 1; ++i) {
                q_minus_t[i] = (mod - q[i]) % mod;
            }

            vector<t> R = mul(q, q_minus_t);
            filter(n, k, R, a, q);

            n = n / 2;
        }
    }

    static void filter(int n, int k, vector<t> &R, vector<t> &a, vector<t> &q) {
        for (int i = 0; i < k + 1; ++i) {
            q[i] = R[2 * i];
        }

        for (int i = n % 2; i < 2 * k; i += 2) {
            a[i / 2] = a[i];
        }
    }

};


static t get(int i, vector<t> &f) {
    return i >= f.size() ? (t) 0 : f[i];
}

static vector<t> mul(vector<t> &p, vector<t> &q) {
    vector<t> result(p.size() + q.size() - 1, 0);
    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j <= i; ++j) {
            result[i] = (result[i] + (get(j, p) * get(i - j, q)) % mod) % mod;
        }
    }
    return result;
}

static void filter(t n, t k, vector<t> &R, vector<t> &a, vector<t> &q) {

    for (int i = n % 2 == 0 ? 0 : 1; i < 2 * k; i += 2) {
        a[i / 2] = a[i];
    }

    for (int i = 0; i < k + 1; ++i) {
        q[i] = get(2 * i, R);
    }

}

static t get_nth(t n, t k, vector<t> &a, vector<t> &c) {
    vector<t> q(c);
    for (int i = 1; i <= k; ++i) {
        q[i] = (mod - c[i]) % mod;
    }

    while (n >= k) {
        for (int i = k; i < 2 * k; ++i) {
            t res = 0;
            for (int j = 1; j <= k; ++j) {
                res = (res + mod - (q[j] * get(i - j, a)) % mod) % mod;
            }
            a[i] = res;
        }

        vector<t> q_minus_t(q);
        for (int i = 1; i < k + 1; i += 2) {
            q_minus_t[i] = (mod - q[i]) % mod;
        }

        vector<t> R = mul(q, q_minus_t);
        filter(n, k, R, a, q);

        n = n / 2;
    }
    return a[n];
}


int main() {
    t n, k;
    cin >> k >> n;
    vector<t> a(2 * k, 0);
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
    }
    vector<t> c(k + 1, 1);
    for (int i = 0; i < k; ++i) {
        cin >> c[i + 1];
    }
    cout << get_nth(n - 1, k, a, c);


}
