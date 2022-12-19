//
// Created by Grigorii Rassadnikov on 11.12.2022.
//

#include <iostream>
#include <vector>

using namespace std;


int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        int mn=1;
        int last =1;
        int cnt0= 0 ;
        int cnt1= 0;
        int cnt0r= 0 ;
        int cnt1r= 0;
        int ans=1;
        int balance=0;
        if (s[0]=='1'){
            cnt1++;
            cnt1r++;
        }else{
            cnt0++;
            cnt0r++;
        }

        for (int i=1;i<n;i++) {
            int x = s[i]-'0';


            if(cnt1>cnt0 && x==0 || cnt0>cnt1 && x==1) {
                int ab = abs(cnt1 - cnt0);
                int k = 0;
                int fl=0;
                while (mn>1 && k < ab) {
                    mn /= 2;
                    k++;
                    if (x==1){
                        cnt1++;
                    }else{
                        cnt0++;
                    }
                    fl=1;
                }
                if (k<ab) {
                    if (x == 1) {
                        cnt1++;
                    } else {
                        cnt0++;
                    }
                }
            }else if (cnt1>cnt0 && x==1 || cnt0>cnt1 && x==0){
                mn*=2;

            }else{

            }

            int max_else = abs(cnt0-cnt1);


            if (x==1){
                cnt1++;
                cnt1r++;
            }else{
                cnt0++;
                cnt0r++;
            }

//            if(cnt1>cnt0 && x==1 && balance==-1){
//                mn*=2;
//            }else if(cnt0>cnt1 && x==0 && balance==1){
//                mn*=2;
//            }else{
//                if (x==1){
//                    balance++;
//                }else{
//                    balance--;
//                }
//            }
            mn%=998244353;
            ans+=mn;
            ans%=998244353;
//            cout << "-" << mn << endl;


        }
        cout << ans << "\n";

    }

    return 0;
}

