//
// Created by Grigorii Rassadnikov on 26.01.2023.
//

#include <vector>
#include <algorithm>
#include <string>
#include <deque>
#include <map>
#include <set>
#include <cmath>
#include <iomanip>
#include <iostream>
#include<fstream>
#include <queue>
#include <unordered_set>

#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("section-anchors")
#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("data-sections")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")
#pragma GCC optimize("unroll-loops,O3")

using namespace std;

vector <int> z_func(string s) {
    vector <int> z(s.length(), 0);
    z[0] = s.length();
    int left = 0,right=0;
    for (int i = 1; i < s.length(); i++) {
        z[i] = min(z[i - left], right - i);
        z[i] = max(z[i], 0);
        while (z[i] + i < s.length() && s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if (z[i] + i > right) {
            right = z[i] + i;
            left = i;
        }
    }
    return z;
}

int main(){
    string s;
    cin >> s;
    vector <int> z = z_func(s);
    int n = s.size();
    for (int i = 1; i < z.size(); i++) {
        int ind = i;
        while (ind < n) {
            if (i + ind == n && z[ind] >= i) {
                cout << i;
                return  0;
            }
            if (z[ind] >= i) {
                ind += i;
            }
            else {
                break;
            }

        }
    }
    cout << z.size();

}