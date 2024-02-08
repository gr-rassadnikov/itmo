#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<bool> used(n + 1, false);
    int max_kom = n;
    for (int i = 0; i < n; ++i) {
        int v = a[i];
        used[v] = true;
        while (used[max_kom]) {
            cout << max_kom << " ";
            max_kom--;
        }
        cout << "\n";
    }
}