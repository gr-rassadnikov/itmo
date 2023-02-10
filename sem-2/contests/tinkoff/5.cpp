#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a;
    int b = 1;
    for (int i = 0; i < n; i++) {
        a.push_back(i + 1);
        b = b * (i + 1);
    }
    int ans = 0;
    while (b--) {
        int summ = 0;
        for (int i = 0; i < n; i++) {
            summ += (i + 1) * a[i];
        }
        if (summ % k == 0) {
            ans++;
        }
        next_permutation(a.begin(), a.end());
    }
    cout << ans;


    return 0;
}
