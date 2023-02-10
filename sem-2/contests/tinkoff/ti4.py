def color(c):
    if c=='z':
        c='a'
    else:
        c=chr(ord(c)+1)
    return c

n=int(input())
d=[[0 for j in range(n)]for i in range(n)]
c='a'
for i in range(n):
    d[i][i]=c
    d[n-i-1][i]=c

while True:
    last=c
    c=color(c)
    su=0
    for i in range(n):
        for j in range(n):
            if d[i][j]==0:
                su+=1
            if d[i][j]==last:
                if i==0:
                    if d[i+1][j]==0:
                        d[i+1][j]=c
                elif i==n-1:
                    if d[i-1][j]==0:
                        d[i-1][j]=c
                else:
                    if d[i+1][j]==0:
                        d[i+1][j]=c
                    if d[i-1][j]==0:
                        d[i-1][j]=c

                if j==0:
                    if d[i][j+1]==0:
                        d[i][j+1]=c
                elif j==n-1:
                    if d[i][j-1]==0:
                        d[i][j-1]=c
                else:
                    if d[i][j+1]==0:
                        d[i][j+1]=c
                    if d[i][j-1]==0:
                        d[i][j-1]=c

    if su==0:
        break
for i in d:
    print(*i, sep="")
            
                        
                    
