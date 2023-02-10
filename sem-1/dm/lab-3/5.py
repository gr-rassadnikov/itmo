n,k=map(int,input().split())

a=[str(i) for i in range(k)]
for i in range(n-1):
    s=a
    b=[]
    for j in range(0,k):
        for h in s:
            b.append(str(j)+h)

        s.reverse()
    a=b


for i in a:
    print(i)
