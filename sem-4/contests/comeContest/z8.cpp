//
// Created by Grigorii Rassadnikov on 13.02.2023.
//

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define input(a) \
for (int =0; i < a.size(); i++){ \
    cin >> a[i];\
}

#define ll long long

int main() {
    int k;
    cin >> k;
    int xMin = 1e9;
    int yMin = 1e9;
    int xMax = -1e9;
    int yMax = -1e9;

    while (k--) {
        int x, y;
        cin >> x >> y;
        xMin = min(xMin, x);
        xMax = max(xMax, x);
        yMin = min(yMin, y);
        yMax = max(yMax, y);
    }

    cout << xMin << " " << yMin << " " << xMax << " " << yMax << "\n";

    return 0;
}
