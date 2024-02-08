#include <iostream>
#include<vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;


int lastCheck(int n, map<int, int> &toCategory, vector<int> &permetation) {
    map<int, int> d;
    int ans = n;

    for (int i = 0; i < n; ++i) {
        int pr;
        pr = permetation[i];
        int cat = toCategory[pr];
        if (d.contains(cat)) {
            ans = min(ans, i - d[cat]);
        }
        d[cat] = i;
    }
    return ans;
}


pair<bool, vector<int>> check(int dist, int n, vector<pair<int, int>> &sorted) {
    vector<int> position(n, -1);
    int cntBlock = (n + dist - 1) / dist;
    vector<set<int>> blocks(cntBlock);


    int capacity = 0;
    int index = 0;

    for (auto e: sorted) {
        int cnt = e.first;
        int cat = e.second;
        while (cnt > 0) {
            if (position[index] != -1) {
                return {true, position};
            }
            int block = index / dist;
            if (blocks[block].contains(cat)) {
                return {false, {}};
            }

            position[index] = cat;
            blocks[block].insert(cat);
            index += dist;
            if (index >= n) {
                index = ++capacity;
            }
            cnt--;
        }
    }
    return {true, position};
}


int main() {
    int n;
    cin >> n;
    map<int, int> toCategory;
    map<int, vector<int>> data;
    vector<pair<int, int>> sorted;
    for (int i = 0; i < n; ++i) {
        int product, category;
        cin >> product >> category;
        toCategory[product] = category;
        data[category].push_back(product);
    }

    for (auto i: data) {
        sorted.push_back({i.second.size(), i.first});
    }
    std::sort(sorted.begin(), sorted.end());
    std::reverse(sorted.begin(), sorted.end());

    for (int i = n; i >= 0; i--) {
        auto [fl, pos] = check(i, n, sorted);
        if (fl) {
//            if (i == (lastCheck(n, toCategory, pos) + 1) % (n )) {
                for (int p: pos) {
                    cout << data[p].back() << " ";
                    data[p].pop_back();
                }
                return 0;
//            }/*/
        }
    }
    return -1;
}