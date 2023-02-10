#include <iostream>

using namespace std;

int main() {
    int a, b, n;
    cin >> a >> b >> n;
    if (a > (b + n - 1) / n) {
        cout << "Yes";
    } else {
        cout << "No";
    }
    return 0;
}
