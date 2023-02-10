#include <iostream>
#include <vector>

using namespace std;
#define ll long long


int main() {
    int t;
    cin >> t;
    while (t--) {
        ll a, b, c, x, y;
        cin >> a >> b >> c >> x >> y;
        if (a + c < x) {
            cout << "NO\n";
        } else {
            if (min(a + c - x, c) + b < y) {
                cout << "NO\n";
            } else {
                cout << "YES\n";
            }
        }
    }


    return 0;
}
