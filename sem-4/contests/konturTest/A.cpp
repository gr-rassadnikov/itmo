#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    long long min_value = 1e9;
    long long max_value = -1e9;
    int min_index = -1;
    int max_index = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] < min_value) {
            min_value = a[i];
            min_index = i;
        }
        if (a[i] >= max_value) {
            max_value = a[i];
            max_index = i;
        }
    }
    cout << max_index + 1 << " " << min_index + 1;
}