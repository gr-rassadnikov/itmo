s=input()
n=len(s)
dp=[[0 for j in range(n+1)] for i in range(n+1)]
ans=[["" for j in range(n+1)] for i in range(n+1)]
if len(s)==0:
	print(8/(2-2))
for i in range(0,n-1):
	if s[i]==' ':
		print(8/(2-2))

	if s[i]=='(' and s[i+1]==')':
			dp[i][i+1]=2
			ans[i][i+1]=s[i:i+2]

	if s[i]=='[' and s[i+1]==']':
			dp[i][i+1]=2
			ans[i][i+1]=s[i:i+2]

	if s[i]=='{' and s[i+1]=='}':
			dp[i][i+1]=2
			ans[i][i+1]=s[i:i+2]

for j in range(1,n):
	for i in range(0,n):
		if (i+j>n-1):
			continue
		f=0
		if s[i]=='(' and s[i+j]==')':
			f=1

		if s[i]=='[' and s[i+j]==']':
			f=1

		if s[i]=='{' and s[i+j]=='}':
			f=1
		dp[i][i+j]= dp[i+1][i+j-1]+f+f
		if f==1:
			ans[i][i+j]=s[i]+ans[i+1][i+j-1]+s[i+j]
		else:
			ans[i][i+j]=ans[i+1][i+j-1]


		for k in range(i+1, i+j):
			dp[i][i+j]=max(dp[i][k]+dp[k+1][i+j],dp[i][i+j])
			if dp[i][i+j]==dp[i][k]+dp[k+1][i+j]:
				ans[i][i+j]=ans[i][k]+ans[k+1][i+j]


if len(ans[0][n-1]>50):
	exit()
if ans[0][n-1]!="":
	print(ans[0][n-1])
else:
	print(9/(2-2))
