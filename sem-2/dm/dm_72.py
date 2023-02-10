import math
h=0
h_con=0
h_summ=0
f=dict()
for i in range(16):
    s=bin(i)
    if len(s)==3+2:
        s=s[:2]+"0"+s[2:]
    if len(s)==2+2:
        s=s[:2]+"00"+s[2:]
    if len(s)==1+2:
        s=s[:2]+"000"+s[2:]
    y1=int(s[2])+int(s[4])
    y2=int(s[2])+int(s[3])
    y4=int(s[2])+int(s[3])+int(s[4])+int(s[5])
    y1%=2
    y2%=2
    y4%=2
    x=str(y1)+str(y2)+s[2]+str(y4)+s[3:]
    if x in f:
            f[x]+=1
    else:
            f[x]=1
    for i in range(len(x)):
        xx=x
        if xx[i]=='0':
            xx=xx[:i]+"1"+xx[i+1:]
        else:
            xx=xx[:i]+"0"+xx[i+1:]
            
        if xx in f:
            f[xx]+=1
        else:
            f[xx]=1

ans =0
for i in f.values():
    p=int(i)/len(f)
    ans+=p*math.log2(1/p)

for i in f:
    print(i,f[i])

    
