//
// Created by Grigorii Rassadnikov on 26.01.2023.
//

#include <iostream>
#include <vector>

using namespace std;

vector<int> pref(string s) {
    vector<int> pi(s.length());
    for (int i = 1; i < s.length(); ++i) {
        int p = pi[i - 1];
        while (p != 0 && s[i] != s[p])
            p = pi[p - 1];
        if (s[i] == s[p]) {
            p++;
        }
        pi[i] = p;
    }
    return pi;
}

int main() {
    string p, t;
    cin >> p >> t;
    string st = p + "@" + t;
    vector array = pref(st);
    int n = p.length();
    vector<int> ans;
    for (int i = 0; i < st.length(); ++i) {
        if (array[i] == n) {
            ans.push_back(i - n - n + 1);
        }
    }
    cout << ans.size() << "\n";
    for (int i: ans) {
        cout << i << " ";
    }

    return 0;
}