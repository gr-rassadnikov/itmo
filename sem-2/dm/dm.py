cnt=0
d=0
for k in range(4):
    for i in range(52):
        x=i%4
        for j in range(52):
            if j!=i:
                cnt+=1
                y=j%4
                if x==y or x==k or y==k:
                    d+=1
            
