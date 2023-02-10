#include <iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
    int n;
    cin >> n;
    int k = 1;
    for (int i = 0; i < n; i++) {
        k = k * 2;
    }
    vector <int> d;
    int num =n;
    vector <string> ans;
    vector <int> no(n,-1);
    vector <int> mo(n,-1);
    for (int i = 0; i < k; i++) {
        string s;
        int v;
        cin >> s >> v;
        if (v==1){
            for (int j=0;j<n;j++){
                if (s[j]=='0' && no[j]==-1){
                    ans.push_back(to_string(1)+" "+ to_string(j+1));
                    num++;
                    no[j]=num;

                }
                if (j==1 && s[j]=='1' && s[j-1]=='1'){
                    ans.push_back(to_string(2)+" "+ to_string(j+1)+" "+ to_string(j-1+1));
                    num++;
                    mo[j] = num;

                }
                if (j==1 && s[j]=='1' && s[j-1]=='0'){
                    ans.push_back(to_string(2)+" "+ to_string(j+1)+" "+ to_string(no[j-1]));
                    num++;
                    mo[j] = num;

                }
                if (j==1 && s[j]=='0' && s[j-1]=='1'){
                    ans.push_back(to_string(2)+ " "+to_string(no[j])+" "+ to_string(j-1+1));
                    num++;
                    mo[j] = num;

                }
                if (j==1 && s[j]=='0' && s[j-1]=='0'){
                    ans.push_back(to_string(2)+" "+ to_string(no[j])+" "+ to_string(no[j-1]));
                    num++;
                    mo[j] = num;

                }


                if (j>1 && s[j]=='1'){
                    ans.push_back(to_string(2)+" "+ to_string(j+1)+" "+ to_string(mo[j-1]));
                    num++;
                    mo[j] = num;

                }


                if (j>1 && s[j]=='0'){
                    ans.push_back(to_string(2)+ " "+to_string(no[j])+" "+ to_string(mo[j-1]));
                    num++;
                    mo[j] = num;

                }
            }
            d.push_back(num-1);

        }


    }
    for (int i=1;i<d.size();i++){
        if (i>1){
            ans.push_back(to_string(3)+" "+ to_string(num)+ " "+to_string(d[i]+1));
            num++;
        }
        else{
            ans.push_back(to_string(3)+" "+ to_string(d[i-1]+1)+" "+ to_string(d[i]+1));
            num++;
        }
    }
    if (ans.size()==0){
        ans.push_back(to_string(1)+" "+ to_string(1));
        ans.push_back(to_string(2)+" "+ to_string(1)+" "+ to_string(n+1));
    }

    cout << ans.size()+n << endl;

    for (auto i:ans){
        cout << i << endl;
    }
    return 0;
}
