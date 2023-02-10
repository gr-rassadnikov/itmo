
def f(y,a,k, n):
    su=0
    cnt=1
    for i in range(n):
        if a[i]>y:
            return 0
        if (su + a[i] > y):
            cnt += 1
            su = a[i]
        else :
            su += a[i]
        

    if (cnt>k):
        return 0
    
    return 1


n,k=map(int,input().split())
a=[int(i) for i in input().split()]
l=-1
r=0
for i in range(n):
    r+=a[i]
r+=1
while (r>l+1):
    m=(r+l)//2;
    if (f(m,a,k,n)):
        r=m
    else:
        l=m

print(r)
