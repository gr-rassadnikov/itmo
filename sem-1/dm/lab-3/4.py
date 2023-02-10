n=int(input())
i ='0'*n
a=set()
a.add(i)
s=set()

while 1:
    d = i[1:n]
    if  d+'1' not in a:
      i = d + '1'
    elif d + '0' not in a:
      i = d + '0'
    else:
      break
    a.add(i)

for i in a:
    print(*i, sep="")