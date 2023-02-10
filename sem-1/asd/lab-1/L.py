def f(x,n):
    su=0
    for i in range(1,n+1):
        p=(x-1)//i
        if p>n:
            p=n+1-1
        su+=p
    
    return su

        
    


    
    
n,k=map(int,input().split())
l=0
r=n*n+1
while r>l+1:
    m=(r+l)//2
    if f(m,n)<k:
        l=m
    else:
        r=m

print(l)
