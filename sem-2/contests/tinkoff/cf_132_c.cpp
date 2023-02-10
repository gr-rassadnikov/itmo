#include <iostream>
#include <vector>

using namespace std;
#define ll long long


bool check(string &s) {
    int b = 0;
    for (auto i: s) {
        if (i == '(') {
            b++;
        } else {
            b--;
        }
        if (b < 0) {
            return false;
        }
    }
    if (b < 0) {
        return false;
    }
    return true;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int cnt_l = std::count(s.begin(), s.end(), '(');
        int cnt_r = std::count(s.begin(), s.end(), ')');
        if (std::count(s.begin(), s.end(), '?') == 0) {
            cout << "YES\n";
            continue;
        }
        int need_l, need_r;

        if (cnt_l < cnt_r) {
            need_l = cnt_r - cnt_l;
            need_r = (s.size() - cnt_l - cnt_r - need_l) / 2;
            need_l += need_r;
        } else {
            need_r = cnt_l - cnt_r;
            need_l = (s.size() - cnt_r - cnt_l - need_r) / 2;
            need_r += need_l;
        }
        int next_l = -1;
        while (need_l > 1) {
            for (int i = next_l + 1; i < s.size(); i++) {
                if (s[i] == '?') {
                    s[i] = '(';
                    next_l = i;
                    break;
                }
            }
            need_l--;
        }
        string first = s;
        string second = s;
        if (need_l != 1) {
            cout << "YES\n";
            continue;
        }
        for (int i = next_l + 1; i < first.size(); i++) {
            if (s[i] == '?') {
                first[i] = '(';
                second[i] = ')';
                next_l = i;
                break;
            }
        }

        int used = 0;
        for (int i = next_l + 1; i < first.size(); i++) {
            if (s[i] == '?') {
                first[i] = ')';
                if (used == 0) {
                    second[i] = '(';
                    used = 1;
                } else {
                    second[i] = ')';
                }
            }
        }
        if (check(first) && !check(second) || first == second) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }


    }


    return 0;
}
