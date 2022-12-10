#include <iostream>
#include <vector>

using namespace std;

int main() {

    int n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int last = a[0] - 2;
    for (int i = 0; i < n; i++) {
        a[i] -= (i + 1);
        a[i] = max(a[i], last + 1);
        last = a[i];
    }

    for (auto i: a) {
        cout << i << "\n";
    }

    return 0;
}
