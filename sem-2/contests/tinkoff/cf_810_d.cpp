#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;
#define ll long long


int main() {
    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;
        vector<int> d(3, 0);
        cin >> d[0] >> d[1] >> d[2];
        vector<int> u(3, 0);

        u[x - 1] = 1;

        while (true) {
            x = d[x - 1];
            if (x==0 || u[x - 1] == 1) {
                break;
            }
            u[x - 1] = 1;
        }
        if (u[0] + u[1] + u[2] == 3) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }

    }


    return 0;
}
