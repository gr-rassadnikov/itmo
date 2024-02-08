#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int last_a = -1;
    int last_b = -1;
    int last_c = -1;
    int last_d = -1;

    int res = 1e9;

    for (int i = 0; i < n; ++i) {
        if (s[i] == 'a') {
            last_a = i;
        } else if (s[i] == 'b') {
            last_b = i;
        } else if (s[i] == 'c') {
            last_c = i;
        } else if (s[i] == 'd') {
            last_d = i;
        }
        int last = min(min(last_a, last_b), min(last_c, last_d));

        if (last == -1) {
            continue;
        }

        int size = i - last + 1;
        if (size < res) {
            res = size;
        }

    }
    if (res == 1e9) {
        cout << -1;
    } else {
        cout << res;
    }


    return 0;
}