n,k=map(int,input().split())
import math
per=[]
w=set()



for i in range(n):

    f = k // math.factorial(n - i-1)
    k =k% math.factorial(n - i-1)
    cnt=0

    for j in range(n):
      if j not in w:
        cnt+=1
        if cnt-f==1:
          per.append(j+1)
          w.add(j)

print(*per)