#include <iostream>
#include <vector>

using namespace std;
int dp[100000][11];
int main() {
    int n, k;
    cin >> n >> k;
    int mod= 1e9+7;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = 0;
        }
    }


    int ans=0;
    for (int i = 0; i < n; i++) {
        dp[i][1]++;
        dp[i][1]%=mod;
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                for (int s = 1; s < k; s++) {
                    dp[j][s + 1] += dp[i][s]%=mod;
                    dp[j][s + 1]%=mod;
                }
            }
        }
        ans+=dp[i][k]%mod;
        ans%=mod;
    }
    cout << ans%mod;

    return 0;
}
