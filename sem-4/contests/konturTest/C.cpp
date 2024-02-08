#include <iostream>
#include <vector>
#include <set>

using namespace std;
#define ll long long

bool condition(set<int> &zeroes, ll sum, ll k) {
    if (zeroes.size() > 1 || sum > k) {
        return false;
    }
    return true;
}

int main() {
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> zero(n, 0);
    for (int i = 0; i < n; i++) {
        if (i == 0 && a[i] == 0) {
            zero[i] = 1;
            continue;
        }
        zero[i] = zero[i - 1];
        if (a[i] == 0) {
            zero[i] += 1;
        }
    }

    long long result = 0;
    int l = 0;
    int r = 0;
    set<int> zeroes;
    long long sum = 0;
    sum += a[l];
    if (a[l] == 0) {
        zeroes.insert(l);
    }

    while (r < n) {
        while (!condition(zeroes, sum, k) && l < r) {
            zeroes.erase(l);
            sum -= a[l];
            l++;
        }

        if (condition(zeroes, sum, k)) {
            result += (r - l + 1);
        }

        r++;
        sum += a[r];
        if (a[r] == 0) {
            zeroes.insert(r);
        }
    }
    cout << result;
}
