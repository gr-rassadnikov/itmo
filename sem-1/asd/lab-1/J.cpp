#include <iostream>
#include <vector>
using namespace std;

int f(int y, vector <int> &a, int k, int n){
    int su=0;
    int cnt=1;
    for (int i=0;i<n;i++) {
        if (su + a[i] > y) {
            cnt += 1;
            su = a[i];
        } else {
            su += a[i];
        }

    }
    if (cnt>k) {
        return 0;
    }
    return 1;
}
int main() {
    int n,k;
    cin >> n >> k;
    vector <int> a(n);
    int l=-1;
    int r=0;
    for (int i=0;i<n;i++){
        cin >> a[i];
        r+=a[i];
    }
    l =r/k -2;
    r++;

    while (r>l+1){
        int m=(r+l)/2;
        if (f(m,a,k,n)){
            r=m;
        }
        else{
            l=m;
        }
    }
    cout << r;



}