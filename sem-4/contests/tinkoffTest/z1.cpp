#include <iostream>

using namespace std;

int main() {
    int h1, h2, h3, h4;
    cin >> h1 >> h2 >> h3 >> h4;
    if (h1 >= h2 && h2 >= h3 && h3 >= h4 || h1 <= h2 && h2 <= h3 && h3 <= h4) {
        cout << "YES";
    } else {
        cout << "NO";
    }

}
