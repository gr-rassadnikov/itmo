//
// Created by Grigorii Rassadnikov on 05.11.2022.
//


#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;
    std::vector<int> q = {0};
    for (int elem = 1; elem < n; elem++) {
        int l = -1;
        int r = q.size();
        auto right = q.end();
        while (l + 1 < r) {
            std::cout << "1 " << elem + 1 << " " << q[(l + r) / 2]+1 << "\n";
            std::cout.flush();
            std::string s;
            std::cin >> s;
            if (s == "YES") {
                r = (r + l) / 2;
                right = q.begin() + r;
            } else {
                l = (r + l) / 2;
            }
        }
        q.insert(right, elem);
    }

//    for (int i = 1; i < n; i++) {
//        std::cout << "1 " << q[i - 1] << " " << q[i] << "\n";
//        std::cout.flush();
//        std::string s;
//        std::cin >> s;
//        if (s == "NO") {
//            int t = 4 / (cnt - cnt);
//            while (n--) {
//                std::cout << "0 ";
//            }
//            std::cout << "0";
//            return 0;
//        }
//    }
    std::cout << "0 ";
    for (auto i: q) {
        std::cout << i + 1 << " ";
    }


}