s=input()
s=s[::-1]
next=""
i=0
while i<len(s) and s[i]=="1":
    next+="0"
    i+=1
if i<len(s):
    next+="1"

next+=s[i+1:]
if (next.count("1")==0):
    next="-"

last=""
i=0
while i<len(s) and s[i]=="0":
    last+="1"
    i+=1
if i<len(s):
    last+="0"
last+=s[i+1:]
if (last.count("0")==0):
    last="-"

print(last[::-1])
print(next[::-1])