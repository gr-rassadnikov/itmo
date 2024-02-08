#include <iostream>
#include <vector>
#include <set>


using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> d(2e5 + 1, 0);
    set<pair<int, int>> f;
    int res = -1;
    for (int i = 0; i < n; ++i) {
        f.erase(make_pair(d[a[i]], a[i]));
        d[a[i]]++;
        f.insert(make_pair(d[a[i]], a[i]));


        int min_value = f.begin()->first;
        int max_value = f.rbegin()->first;
        if (min_value == max_value) {
            res = i;
            continue;
        }

        bool min_is_single = true;
        bool max_is_single = true;

        bool is_second_equal_end = false;

        if (++f.begin() != f.end()) {
            if ((++f.begin())->first == min_value) {
                min_is_single = false;
            }
            if ((--(--f.end()))->first == max_value) {
                max_is_single = false;
            }

            if ((++f.begin())->first == max_value) {
                is_second_equal_end = true;
            }
        }

        if (min_value + 1 == max_value && max_is_single) {
            res = i;
        }
        if (min_value == 1 && min_is_single && is_second_equal_end) {
            res = i;
        }
    }
    cout << res + 1;

}
