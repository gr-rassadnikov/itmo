#include <iostream>
#include <vector>

#define ll long long

using namespace std;
const ll mod = 1e9 + 7;


void propogate_dp(int i, int k, vector<ll> &c, vector<ll> &dp, vector<ll> &s) {
    for (int j = 0; j < k; ++j) {
        if (i < c[j]) {
            continue;
        }
        dp[i] = (dp[i] + s[i - c[j]]) % mod;
    }
}

void propogate_s(int i, vector<ll> &dp, vector<ll> &s) {

    for (int j = 0; j <= i; ++j) {
        s[i] = (s[i] + dp[j] * dp[i - j] % mod) % mod;
    }
}

int main() {

    int k, m;
    cin >> k >> m;

    vector<ll> c(k);
    for (int i = 0; i < k; ++i) {
        cin >> c[i];
    }

    vector<ll> dp(m + 1, 0);
    vector<ll> s(m + 1, 0);
    s[0] = 1;
    dp[0] = 1;

    for (int i = 1; i <= m; ++i) {
        propogate_dp(i, k, c, dp, s);
        propogate_s(i, dp, s);
    }


    for (int i = 0; i < m; ++i) {
        cout << dp[i +1] << " ";
    }


}
