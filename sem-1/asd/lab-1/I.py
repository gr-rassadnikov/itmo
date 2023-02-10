def g(x,p,f,a):
    return ((1-a)**2 + x**2)**0.5/p + (a**2 + (1-x)**2)**0.5/f
    
p,f=map(int,input().split())
a=float(input())
l=0.0
r=1.0
while r-l>0.000001:
    m1=(l+l+r)/3
    m2=(l+r+r)/3
    if g(m1,p,f,a)>g(m2,p,f,a):
        l=m1
    else:
        r=m2

print(l)
    
