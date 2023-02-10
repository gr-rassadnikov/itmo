#include <iostream>
#include <vector>
using namespace std;
vector <int> a;
void insert(int x){
    a.push_back(x);
    int i=a.size()-1;
    while (i>0 && a[i]>a[(i-1)/2]){
        swap(a[i],a[(i-1)/2]);
        i=(i-1)/2;
    }

}
int remove(){
    int ans= a[0];
    swap(a[0],a[a.size()-1]);
    a.pop_back();
    int i=0;
    while (2*i+1<a.size()){
        int j=2*i+1;
        if (j+1 < a.size() && a[j+1]>a[j]){
            j++;
        }
        if (a[i]>=a[j]){
            break;
        }
        else {
            swap(a[i], a[j]);
        }
        i=j;
    }
    return ans;
}


int main (){
    int n;
     cin >> n;
     while (n--){
         int fl;
         cin >> fl;
         if (fl==0){
             int x;
             cin >> x;
             insert(x);
         }
         else{
             cout << remove() << endl;
         }
     }
}