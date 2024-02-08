#include <iostream>
#include<vector>
#include <map>

using namespace std;

int main() {
    int n;
    string day;
    cin >> n >> day;
    map<string, int> d = {
            {"Monday",    0},
            {"Tuesday",   1},
            {"Wednesday", 2},
            {"Thursday",  3},
            {"Friday",    4},
            {"Saturday",  5},
            {"Sunday",    6},
    };
    vector<string> ans;
    int from = d[day];
    for (int i = 0; i < from; i++) {
        ans.push_back("..");
    }
    for (int i = 1; i <= n; i++) {
        if (i < 10) {
            ans.push_back("." + to_string(i));
        } else {
            ans.push_back(to_string(i));
        }
    }

    for (int i = 0; i < ans.size(); i++) {
        if (i != 0 && i % 7 == 0) {
            cout << "\n";
        }
        cout << ans[i] << " ";

    }


}