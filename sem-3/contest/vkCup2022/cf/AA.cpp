//
// Created by Grigorii Rassadnikov on 15.01.2023.
//

#include <iostream>
#include <vector>

using namespace std;

int main() {

    int t;
    cin >> t;
    while (t--) {
        int w, d, h;
        cin >> w >> d >> h;
        int a, b, f, g;
        cin >> a >> b >> f >> g;
        int ans = h;
        int e1 = min(a + f, w - a + w - f) + abs(b - g);
        int e2 = min(b + g, d - b + d - g) + abs(a - f);
        cout << ans + min(e1, e2) << "\n";
    }

    return 0;
}
