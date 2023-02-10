import math
h=0
h_con=0
h_summ=0
f=[]
cnt_one=[0 for i in range(20)]
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
    
    d=int(x,2)
    print(x)
    x=x[::-1]
    d_con=int(x,2)
    
    summ=0
    for h in x:
        if h=='1':
            summ+=1

    f.append(x)
    cnt_one[summ]+=1

print("_____")
f.sort()
for i in f:
    print(i)


ans_one=0
for i in range(20):
    print(i,":", cnt_one[i]," ",cnt_one[i]/16)
    if cnt_one[i]!=0:
        ans_one+=cnt_one[i]/16*math.log2(1/(cnt_one[i]/16))


print(ans_one)

    
    
    
