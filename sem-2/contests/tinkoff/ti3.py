s=int(input())
while s%10==0:
    s=s//10
    if s==0:
        break

s=str(s)
print(s.count("0"))
