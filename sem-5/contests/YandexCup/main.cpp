#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    long long k, t;
    cin >> k >> t;

    long long last_min = 1;
    vector<pair<pair<long long, long long>, long long>> d;

    while (k--) {
        long long start, end, dur;
        cin >> start >> end >> dur;
        d.push_back({{start, end},dur});
    }
    std::sort(d.begin(), d.end(), [](auto &l, auto &r){
        return l.first < r.first
                || l.first == r.first && l.second > r.second;
    });

    for (auto i : d) {
//        cout << i.first.first;
        long long start = i.first.first;
        long long end = i.first.second;
        long long dur = i.second;

        if (last_min < end) {
            cout << "No";
            return 0;
        }
        long long loc_min = start + dur;
        last_min = last_min > loc_min ? last_min : loc_min;
    }
    if (last_min < t) {
        cout << "No";
        return 0;
    }

    cout << "Yes";
    return 0;
}
