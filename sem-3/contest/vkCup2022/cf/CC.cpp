//
// Created by Grigorii Rassadnikov on 15.01.2023.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<pair<int, int>> d(26);
        for (int i = 0; i < 26; ++i) {
            d[i] = {0, 'a' + i};
        }
        for (auto i: s) {
            d[i - 'a'].first++;
        }

        int ans = n;
        vector<int> ff(n);
        std::sort(d.begin(), d.end());
        std::reverse(d.begin(), d.end());

        for (int i = 1; i <= 26; ++i) {
            if (i > n) {
                break;
            }
            if (n % i == 0) {
                int h = n / i;
                map<int, int> stat;
                int sum = 0;
                int sum2 = 0;
                for (int j = 0; j < i; ++j) {
                    stat[d[j].second] = h - d[j].first;
                    sum += max(h - d[j].first, 0);

//                    cout << stat[d[j].second]<<"\n";

                }
                for (int j = i; d[j].first > 0; j++) {
                    stat[d[j].second] = -d[j].first;
                    sum2 += d[j].first;
//                    cout << stat[d[j].second]<<"\n";
                }
                sum2 -= sum;
//                cout << "dd::" << sum2 << endl;

                for (int j = 0; j < 26; ++j) {
                    if (stat.find(j) == stat.end()) {
                        if (sum2 > 0) {
                            stat[j] = min(sum2, h);
                            sum2 -= h;
                        }
                    }
                }
//                for (auto l: stat) {
//                    cout << "d: " << l.first << " " << l.second << endl;
//                }

                if (sum < ans) {
                    ans = sum;
                    vector<int> cop(n, -1);
                    int ind = 0;
                    for (auto ch: s) {
                        int chi = ch;
                        if (stat[chi] < 0) {
                            for (auto element: stat) {
                                if (element.second > 0) {
                                    stat[element.first]--;
                                    stat[chi]++;
                                    ff[ind] = element.first;
//                                    cout << "++";
                                    break;
                                }
                            }
                        } else {
//                            cout << "=";
                            ff[ind] = chi;
                        }
                        ind++;
                    }

                }
            }
        }

        cout << ans << "\n";
        for (int i = 0; i < n; ++i) {
            cout << char(ff[i]);
        }
        cout << "\n";
    }

    return 0;
}
