//
// Created by Grigorii Rassadnikov on 25.01.2023.
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


struct node {
    double x;
    double y;
    int i;
    bool wasUsed = false;
    double min = 1e9;
    int select = -1;

    double dist(node rhs) {
        if (x == rhs.x && y == rhs.y) { return 1e9; }
        return sqrt((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y));
    }
};

int main() {
    int n;
    cin >> n;
    vector<node> g(n);
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        g[i] = {x, y, i};
    }

    double ans = 0;
    for (int i = 0; i < n; ++i) {
        node to = {-1, -1, -1};
        for (node nd: g) {
            if (!nd.wasUsed) {
                if (to.i == -1) {
                    to = nd;
                } else if (nd.min < to.min) {
                    to = nd;
                }
            }
        }
        to.wasUsed = true;
        if (to.select != -1) {
            ans += to.dist(g[to.select]);
        }

        for (node &nd: g) {
            if (nd.dist(to) < nd.min) {
                nd.min = nd.dist(to);
                nd.select = to.i;
            }
        }
        g[to.i] = to;
    }
    cout << ans;

    return 0;
}