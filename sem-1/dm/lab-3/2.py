n=int(input())
a=["0","1"]
for i in range(n-1):
    b=["0"+i for i in a]
    a.reverse()
    for i in a:
        b.append("1"+i)

    a=b

for i in a:
    print(i)
