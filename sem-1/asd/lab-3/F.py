k=[]
def gen_1(g,n):
    if (n==1):
        k.append(g)
        return
    gen_1(g+"0",n-1)
    gen_1(g+"1",n-1)




n=int(input())

gen_1("0", n)
gen_1("1",n)

a=[[0 for i in range(n)]for j in range(n)]

for i in range(n):
	a[i]=[int (j) for j in input().split()]


inf = 10000000000000000

dp=dict()
for i in k:
	dp[i]=[inf for j in range(n)]



inf = 10000000000000000


for mask in k:
	for i in range(n):
		if mask.count("1")==1 and mask[i]=="1":
			dp[mask][i]=0
		elif mask.count("1")>1 and mask[i]=="1":
		
			for j in range(n):
			
				if mask[j]=="1":
					m =mask
					if m[i]=="0":
						m[i]=m[:i]+"1"+m[i+1:]
					else:
						m=m[:i]+"0"+m[i+1:]


					dp[mask][i] = min(dp[mask][i],
						dp[m][j] + a[j][i])




p=inf
h=k[-1]
last=-1
for i in range(n):
	p=min(p, dp[h][i])
	if p==dp[h][i]:
		last=i

ans=[last]
m=h
while len(ans)<n:
	i=last
	h=m
	for j in range(n):
	
		m=m[:i]+"0"+m[i+1:]
		#print(h,m,i,j,dp[h][last],dp[m][j]+a[j][i])

		if dp[h][last]==dp[m][j]+a[j][i] :
			#print("000")
			last=j
			break
	ans.append(last)



print(p)
for i in ans:
	print(i+1, end=" ")





