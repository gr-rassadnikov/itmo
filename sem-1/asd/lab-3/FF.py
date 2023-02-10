n=int(input())
a=[0 for i in range(n+1)]
for i in range(1,n+1):
	a[i]=int(input())


inf=10000000000000
dp=[[inf for j in range(n+1)]for i in range(n+1)]


ans=inf

k1=0

for i in range(0,n+1):

	for j in range(0,n+1):
		if (j>i):
			dp[i][j]=inf
			continue
		if j<=0:
			if i>=1:
				if a[i]<=100:
					dp[i][j]=min(dp[i-1][j+1],dp[i-1][j]+a[i])
				else:
					dp[i][j]=dp[i-1][j+1]
			else:
				dp[i][j]=0
		else:
			if a[i]>100:
				if j==n:

					dp[i][j]=dp[i-1][j-1]+a[i]
				else:
					dp[i][j]=min(dp[i-1][j+1],dp[i-1][j-1]+a[i])
			else:
				if j==n:
					dp[i][j]=dp[i-1][j]+a[i]
				else:	
					dp[i][j]=min(dp[i-1][j+1],dp[i-1][j]+a[i])



ans=inf
k1=0
for j in range(n+1):
		if dp[n][j]<=ans:
			ans=dp[n][j]
			k1=j

if ans==inf:
	print(9/(8-8))
x=k1
y=n
res=[]

while y>0:
	if y>x:
		if x==0:
			if y:
				if a[y]>100:
					res.append(y)
				
					x+=1
				else:
					if dp[y][x]==dp[y-1][x+1]:
						res.append(y)
						x+=1

		else:
			if a[y]<=100:
				if dp[y-1][x+1]==dp[y][x]:
					res.append(y)
					x+=1
			if a[y]>100:
				if dp[y-1][x+1]==dp[y][x]:
					res.append(y)
					
					x+=1
				else:
					
					x-=1
			else:
				if dp[y-1][x+1]==dp[y][x]:
					res.append(y)
				
					x+=1
				
			

	else:
		break
	y-=1


print(ans)
print(k1,len(res),sep=" ")
res.reverse()
for i in res:
	print(i)

