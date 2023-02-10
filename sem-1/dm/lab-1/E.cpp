#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
int f(char c){
    if (c=='1'){
        return 1;
    }
    return 0;
}

int main() {
    int n;
    cin >> n;
    int k = 1;
    for (int i = 0; i < n; i++) {
        k *= 2;
    }
    vector<int> a(k, 0);
    vector <string> mas;
    int ind=0;
    for (int i = 0; i < k; i++) {
        string s;
        cin >> s;
        int v;
        cin >> v;
        a[i] =v;
        mas.push_back(s);
    }
    vector<int> ans;

    while (k--) {
        ans.push_back(a[0]);
        for (int i = 0; i < k; i++) {
            a[i] = (a[i] + a[i + 1]) % 2;
        }

    }
    for (int i=0;i<mas.size();i++) {
        cout <<mas[i] << " " << ans[i] <<endl;
    }

    return 0;
}
