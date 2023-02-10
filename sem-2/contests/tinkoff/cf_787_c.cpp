#include <iostream>
#include <vector>
#include <string>

using namespace std;
#define ll long long

void pr(string &s) {
    int ans = 0;
    int one = s.find('1');
    int zero = s.find('0');
    int q = s.find('?');
    if (find(s.begin(), s.end(), '1') == s.end() && find(s.begin(), s.end(), '0') == s.end()) {
        cout << s.size() << "\n";
        return;
    }
    if (find(s.begin(), s.end(), '1') == s.end()) {
        if (zero == 0) {
            cout << "1\n";
            return;
        } else {
//            ans += zero + 1;
            cout << zero + 1;
            return;
        }
    }
    if (zero < one && find(s.begin(), s.end(), '0') != s.end()) {
        if (zero == 0) {
            cout << "1\n";
            return;
        } else {
            ans += zero + 1;
        }
    }
    if (one < zero) {
        if (s.rfind('1') < zero) {
            ans++;
        }
    }
    int rone = s.rfind('1');
//    cout << ans << " ";
    ans++;
    for (int i = rone + 1; i < s.size(); i++) {
        if (s[i] == '0') {
            break;
        }
        ans++;
    }
    cout << ans << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        pr(s);
    }

    return 0;
}
