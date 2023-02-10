#include <iostream>
#include<vector>
using namespace std;
int main() {
    int n,k;
    cin >> n >> k;
    vector <vector <int>> a(k);
    for (int i=0;i<k;i++){
        for (int j=0;j<n;j++){
            a[i].push_back(0);
            cin >> a[i][j];
        }
    }
    vector <int> zn(n,-1);
    for (int i=0;i<k;i++){
        int q=0;
        for (int j=0;j<n;j++){
            if (a[i][j]!=-1){
                q++;
            }
        }
        if (q==0){
            cout << "YES";
            return 0;
        }
    }
    vector <int> q(k,0);
    while (true){
        int fl=0;

        for(int i=0;i<k;i++){
            vector <int> odin;
            for (int j=0;j<n;j++){
                if (a[i][j]!=-1) {
                    odin.push_back(j);
                }
            }
            if (odin.size()==1){
                if (zn[odin[0]]==-1 || zn[odin[0]] == a[i][odin[0]]) {
                    zn[odin[0]] = a[i][odin[0]];
                }
                else{
                    cout <<"YES";
                    return 0;
                }
                a[i][odin[0]]=-1;
                fl=1;
            }
        }

        for (int i=0;i<k;i++){
            for (int j=0;j<n;j++){
                if (a[i][j]==0 && zn[j]==0 || a[i][j]==1 && zn[j]==1){
                    q[i]=1;
                }

            }
            if (q[i]==1){
                for (int j=0;j<n;j++) {
                    a[i][j] = -1;
                }
            }
            int g=0;
            for (int j=0;j<n;j++){
                if ((zn[j]==1 && a[i][j]==1 || zn[j]==0 && a[i][j]==0)||zn[j]==-1 ){
                    g++;
                }
            }
            if (g==0 && q[i]==0){
                cout << "YES";
                return 0;
            }
        }
        if (fl==0){
            cout << "NO";
            return 0;
        }



    }


    return 0;
}
