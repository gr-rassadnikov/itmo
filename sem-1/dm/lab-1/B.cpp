#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int f(char c) {
    if (c == '1') {
        return 1;
    }
    return 0;
}

int polyng(vector<int> a, int n) {
    if (n==1){
        return 1;
    }
    int k = 1;
    for (int i = 0; i < n; i++) {
        k *= 2;
    }
    int ig=0;
    while (k--) {
        if (ig!=0 && ig!=1 && ig!=2 && ig!=4 && ig!=8 && ig!=16 && ig!=32) {
            if (a[0] == 1) {
                return 0;
            }
        }
        for (int i = 0; i < k; i++) {
            a[i] = (a[i] + a[i + 1]) % 2;
        }
        ig++;

    }
    return 1;
}

int sam(vector<int> a, int k) {
    if (k==1){
        return 0;
    }
    for (int i = 0; i < k ; i++) {
        if (a[i] == a[k - i - 1]) {
            return 0;
        }
    }
    return 1;
}

int monn(vector<int> a, int k, int n) {
    for (int i = 0; i < k; i++) {
        for (int j = i+1 ; j < k; j++) {
            int fl = 1;
            int x=i;
            int y=j;
            while (y > 0 || x > 0) {
                if (y % 2 < x % 2) {
                    fl = 0;
                    break;
                }
                y = y / 2;
                x = x / 2;
            }
            if (fl==1 && a[j]<a[i]){
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    int m;
    cin >> m;
    int l = 0;
    int s0 = 0;
    int s1 = 0;
    int sa = 0;
    int mon = 0;
    for (int i = 0; i < m; i++) {
        int n;
        cin >> n;
        if(n==0){
            int t= 3 /(n-n);
        }
        int k = 1;
        for (int i = 0; i < n; i++) {
            k *= 2;
        }
        string s;
        cin >> s;
        vector<int> a;
        for (int j = 0; j < k; j++) {
            a.push_back(f(s[j]));
        }
        if (polyng(a, n) == 0) {
            l = 1;
        }
        if (a[0] == 1) {
            s0 = 1;
        }
        if (a[k - 1] == 0) {
            s1 = 1;
        }
        if (sam(a, k) == 0) {
            sa = 1;
        }
        if (monn(a,k,n)==0) {
            mon = 1;
        }
    }
    //cout << s0 << s1 << mon << sa << l;
    if (s0*s1*mon*sa*l==0){
        cout << "NO";
    }
    else{
        cout << "YES";
    }
}