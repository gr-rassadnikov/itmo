#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    int get = -1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            get = i;
            break;
        }
    }
    if (get == -1) {
        cout << 1 << " " << n - 1;
    } else {
        int x = n / get;
        cout << x << " " << n - x;
    }


    return 0;
}