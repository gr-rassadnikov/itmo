#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    long long n;
    cin >> n;
    vector<long long> a(n);
    vector<long long> prefix(n, 0);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (i == 0) {
            prefix[i] = a[i];
            continue;
        }
        prefix[i] = prefix[i - 1] + a[i];
    }

    long long res = 0;
    map<long long, int> d;
    long long start = -1;
    d[0] = -1;

    for (int i = 0; i < n; ++i) {
        if (d.find(prefix[i]) != d.end()) {
            long long left = d[prefix[i]];
            res += (left - start + 1) * (n - i);
            start = left+1;
        }
        d[prefix[i]] = i;
    }
    cout << res;
}
