#include <iostream>

using namespace std;

int get(int a, int b, int x, int y){
    int cnt = x/a;
    x-=cnt*a;
    y+=cnt*b;
    return cnt;
}

int fun3(int a, int b, int c, int x, int y, int z,int &ans){
    int x1 =x;
    int y1 = y;
    int z1 = z;
    ans+=get(a,b,x1,y1);
    ans+=get(b,c,y1,z1);
}

int fun2(int a, int b, int x, int y, int &ans){
    int x2 =x;
    int y2 = y;
    ans+= get(a,b,x2,y2);
}

int o(int a, int b, int c, int x, int y, int z){
    int k1 = get(a,c,x,z)+1;
    int k2 = get(b,c,y,z)+1;
    cout << k1*k2 << endl;
    return k1*k2;

}

long long sum = 0;

void forEach(int a, int x){
    sum+=x/a;
}

int main(){
    int a,b,c,x,y,z;
    cin >> a >> b >> c;
    cin >> x >> y >> z;

    forEach(a,x);
    forEach(b,y);
    forEach(c,z);
    sum+=1;

    cout << sum*(sum+1)/2;




}