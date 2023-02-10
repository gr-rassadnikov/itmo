ans=0
import random

cnt_exp=1000
for i in range(cnt_exp):
    a1=-1
    a2=-1
    a3=-1
    c=0
    while True:
        c+=1
        a1=a2
        a2=a3
        a3=random.randint(0,1)
        if a1==a2 and a2==a3 and a3==0:
           ans+=c
           break
print(ans/cnt_exp)

