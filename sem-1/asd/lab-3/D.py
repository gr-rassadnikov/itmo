s=input()
t = input()
n=len(s)
m=len(t)

d=[[0 for j in range(m+1)]for i in range(n+1)]

for i in range(1,n+1):
	d[i][0] = i
for i in range(1,m+1):
	d[0][i] = i

for i in range(1,n+1):

	for j in range(1,m+1):
		if (s[i-1]==t[j-1]):
			d[i][j]=d[i-1][j-1]
		else:
			d[i][j]=min(d[i-1][j-1],
				d[i-1][j], d[i][j-1])+1



print(d[n][m])