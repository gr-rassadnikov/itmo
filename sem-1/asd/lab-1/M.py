def f(xx, n,k,a,b):
    cnt=0
    for i in range(n):
        x=xx-a[i]-1
        l=-1
        r=n
        while r>l+1:
            m=(r+l)//2
            if b[m]>x:
                r=m
            else:
                l=m
        cnt+=(l+1)

    return cnt

n,k=map(int,input().split())
a=[int(i) for i in input().split()]
b=[int(i) for i in input().split()]
a.sort()
b.sort()

l=0
r=sum(a)+sum(b)+1
while r>l+1:
    m=(r+l)//2
    if f(m,n,k,a,b)<k:
        l=m
    else:
        r=m

print(l)
