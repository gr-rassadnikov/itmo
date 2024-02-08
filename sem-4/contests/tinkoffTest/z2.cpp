#include <iostream>

using namespace std;

int main() {
    long long n, m, k;
    cin >> n >> m >> k;
    cout << (k * n + m - 1) / m;
}