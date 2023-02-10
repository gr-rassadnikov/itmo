#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;
#define ll long long

bool f(int n, int m, vector<int> &a) {
    int cnt = 0;
    int mm = INT_MAX;
    bool was_not = false;
    bool was_2 = false;
    for (auto i: a) {
//        cout << i;
        int cnt_c = i / m;
        if (cnt_c >= 2) {
            cnt += cnt_c;
            if (cnt_c >= 3) {
                was_not = true;
            }else{
                was_2 =true;
            }
        }
    }
    if (n % 2 == 1 && !was_not) return false;
    if (cnt >= n && n%2==0) {
        return true;
    }
    if (cnt >= n && n%2==1 && was_not) {
        return true;
    }
//    if (n % 2 == 1 && was_2 && cnt - 2 >= n) {
//        return true;
//    }
//    if (n % 2 == 1 && !was_2 && cnt >= n) {
//        return true;
//    }
    return false;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> a(k);
        for (int i = 0; i < k; i++) {
            cin >> a[i];
        }
        if (f(n, m, a) || f(m, n, a)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }


    }


    return 0;
}
