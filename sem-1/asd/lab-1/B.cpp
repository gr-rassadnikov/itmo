#include <iostream>
#include <vector>

using namespace std;


int main() {
    int n;
    cin >> n;
    vector <int> a(n);
    vector <int> d(101);
    for (int i=0;i<n;i++){
        cin >> a[i];
        d[a[i]]++;
    }
    for (int i=0;i<d.size();i++){
        while (d[i]>0){
            cout << i << " ";
            d[i]--;
        }
    }

    return 0;
}