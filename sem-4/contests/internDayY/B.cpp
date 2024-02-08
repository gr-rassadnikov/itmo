#include <iostream>
#include<vector>
#include <map>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

struct Pas {
    int row;
    char seat;
    int a;
    bool isOk = false;
    bool wait = false;
    int index = -1;

    Pas(string rowSeat, int a) : a(a) {
        row = stoi(rowSeat.substr(0, rowSeat.size()-1));
        seat = rowSeat[rowSeat.size()-1];
//        if (rowSeat.size() == 2) {
//            row = rowSeat[0] - '0';
//            seat = rowSeat[1];
//        } else {
//            row = (int) (to_string(rowSeat[0]) + rowSeat[1]);
//            seat = rowSeat[2];
//        }
        row--;
    }
};

int getVal(char seat, set<char> &d) {
    if (seat == 'A') {
        if (d.contains('B') && d.contains('C')) {
            return 15;
        } else if (d.contains('B') || d.contains('C')) {
            return 5;
        }
    } else if (seat == 'B') {
        if (d.contains('C')) {
            return 5;
        }
    } else if (seat == 'C' || seat == 'D') {
        return 0;
    } else if (seat == 'E') {
        if (d.contains('D')) {
            return 5;
        }
    } else if (seat == 'F') {
        if (d.contains('D') && d.contains('E')) {
            return 15;
        } else if (d.contains('D') || d.contains('E')) {
            return 5;
        }
    }
    return 0;
}

int main() {
    int n;
    cin >> n;
    vector<Pas> q;
    vector<set<char>> d;
    vector<bool> use(31, false);
    for (int i = 0; i < 31; i++) {
        d.push_back({});
    }
    for (int i = 0; i < n; i++) {
        int a;
        string rowSeat;
        cin >> a >> rowSeat;
        q.push_back(Pas(rowSeat, a));

    }

    for (int t = 0;; t++) {
        bool flag = true;
        for (auto pas: q) {
            if (!pas.isOk) {
                flag = false;
            }
        }
        if (flag) {
            cout << t - 1;
            return 0;
        }
        for (auto &pas: q) {
            if (pas.isOk) {
                continue;
            }
            if (pas.index < pas.row) {
                if (!use[pas.index + 1]) {
                    use[pas.index] = false;
                    pas.index++;
                    use[pas.index] = true;
                }
            }
            if (pas.index == pas.row) {
                if (pas.wait) {
                    pas.a--;
                } else {
                    pas.wait = true;
                    int val = getVal(pas.seat, d[pas.row]);
                    pas.a += val;
                }
                if (pas.a == -1) {
                    pas.isOk = true;
                    use[pas.row] = false;
                    d[pas.row].insert(pas.seat);
                }
            }

        }

    }

}
//6
//0 1A
//0 1B
//0 1C
//0 1D
//0 1E
//0 1F

//6
//0 1A
//0 2B
//0 3C
//0 4D
//0 5E
//0 6F

//6
//10 2C
//20 2B
//30 2A
//10 1D
//10 1E
//10 1F
