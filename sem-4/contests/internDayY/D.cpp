#include <iostream>
#include<vector>
#include <map>
#include <string>
#include <set>
#include <algorithm>

using namespace std;


int main() {
    int n;
    cin >> n;
    map<int, int> toCategory;

    for (int i = 0; i < n; ++i) {
        int product, category;
        cin >> product >> category;
        toCategory[product] = category;
    }

    map<int, int> d;
    int ans = n;

    for (int i = 0; i < n; ++i) {
        int pr;
        cin >> pr;
        int cat = toCategory[pr];
        if (d.contains(cat)) {
            ans = min(ans, i - d[cat]);
        }
        d[cat] = i;
    }
    cout << ans;

}

//5
//1 1
//2 1
//3 1
//4 2
//5 2
//1 4 2 5 3

//9
//0 1
//2 1
//3 1
//4 2
//5 2
//6 2
//7 3
//8 3
//999 3
//0 4 7 2 5 8 3 6 999