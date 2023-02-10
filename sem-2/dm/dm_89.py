n=144
ans=0
import random
for h in range(10000):
    x=0
    for i in range(n):
        a=random.randint(0,1)
        x-=1
        x+=2*a
    ans+=x*x

print(ans/10000)
    
        
