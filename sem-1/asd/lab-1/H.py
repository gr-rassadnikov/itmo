c=float(input())
l=0.0
r=c

while r-l>0.000000001:
    x=(l+r)/2
    if abs(x -(c - x*x)**2)< 0.000000001:
        print(x)
        exit()
    elif x*x + x**0.5 >c:
        r=x
    else:
        l=x

print(r)
        
