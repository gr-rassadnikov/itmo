#include <iostream>
#include <vector>

using namespace std;
long long cnt= 0;

vector <int> merge(vector <int> &x, vector <int> &y){
    vector <int> a;
    int i=0, j=0;
    while (i<x.size() || j< y.size()){
        if (i==x.size()){
            a.push_back(y[j++]);
            continue;
        }
        if (j==y.size()){
            a.push_back(x[i++]);
            continue;
        }
        if (x[i]<=y[j]){
            a.push_back(x[i++]);
        }
        else{
            cnt+=(long long)(x.size()-i);
            a.push_back(y[j++]);
        }
    }

    return a;
}
void sort(vector <int> &a){
    vector <int> x;
    vector <int> y;
    if (a.size()<=1){
        return ;
    }
    for (int i=0;i<(a.size()+1)/2;i++){
        x.push_back(a[i]);
    }
    for (int i=(a.size()+1)/2; i<a.size();i++){
        y.push_back(a[i]);
    }
    sort(x);
    sort(y);
    a = merge(x,y);


}
int main() {
    int n;
    cin >> n;
    vector <int> a(n);
    for (int i=0;i<n;i++){
        cin >> a[i];
    }
    sort(a);
    cout << cnt;

    return 0;
}