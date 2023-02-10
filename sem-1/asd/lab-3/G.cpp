
#include <iostream>
#include <vector>
#include <string>

using namespace std;
int main(){
	string s;
	cin >> s;
	int n=s.size();
	vector <vector <int>> dp(n);
	vector <vector <string>> ans(n);
	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			dp[i].push_back(0);
			ans[i].push_back("");
		}
	}
	
	for (int i =0;i<n-1;i++){

		if (s[i]=='(' && s[i+1]==')'){
				dp[i][i+1]=2;
				string h=s.substr(i,i+2);

				ans[i][i+1]=h;
		}

		if (s[i]=='[' && s[i+1]==']'){
				dp[i][i+1]=2;
				string h=s.substr(i,i+2);

				ans[i][i+1]=h;
		}

		if (s[i]=='{' && s[i+1]=='}'){
				dp[i][i+1]=2;
				string h=s.substr(i,i+2);

				ans[i][i+1]=h;
		}
	}
	

	
	for (int j=1;j<n;j++){
		for (int i=0;i<n;i++){
			if (i+j>n-1){
				continue;
			}
			int f=0;
			if (s[i]=='(' && s[i+j]==')'){
				f=1;
			}

			if (s[i]=='[' && s[i+j]==']'){
				f=1;
			}

			if (s[i]=='{' && s[i+j]=='}'){
				f=1;
			}
			dp[i][i+j]= dp[i+1][i+j-1]+f+f;
			if (f==1){
				ans[i][i+j]=s[i]+ans[i+1][i+j-1]+s[i+j];
			}
			else{
				ans[i][i+j]=ans[i+1][i+j-1];
			}


			for (int k =i+1;k<i+j;k++){
				dp[i][i+j]=max(dp[i][k]+dp[k+1][i+j],dp[i][i+j]);

				if (dp[i][i+j]==dp[i][k]+dp[k+1][i+j]){
					ans[i][i+j]=ans[i][k]+ans[k+1][i+j];
				}
			}
		}	
	}



	if (n>1){	
		cout << ans[0][n-1];
	}else{
		cout <<a[-1][0];
	}
	return 0;
}
