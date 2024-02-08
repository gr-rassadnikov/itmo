#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long k, n;
    cin >> k >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<long long> pow(33, 1);
    for (int i = 1; i < 33; ++i) {
        pow[i] = pow[i - 1] * 2;
    }

    long long result = 1e9 + 1;
    if (n >= 33) {
        for (int i = 33; i < n; ++i) {
            result = min(result, a[i]);
        }
        n = 33;
    }
    long long trata = 0;
    for (int i = n - 1; i >= 0; --i) {
        bool isBetter = true;
        for (int j = 0; j < i; ++j) {
            if (a[i] > a[j] * pow[i - j]) {
                isBetter = false;
            }
        }
        if (isBetter) {
            long long cnt_buy_up = (k + pow[i] - 1) / pow[i];
            long long cnt_buy_low = (k) / pow[i];

            long long cost_buy_up = a[i] * cnt_buy_up;
            long long cost_buy_low = a[i] * cnt_buy_low;

            result = min(result, trata + cost_buy_up);
            trata += cost_buy_low;
            k = k % pow[i];
        }
    }
    cout << result;


}