n=int(input())
a=[int(i) for i in input().split()]


if n==1:
	print(0)
	print(0)
	exit()

ind=n-1
fl=1
for i in range(n):
	if a[i]!=i+1:
		fl=0

if fl:
	print("0 "*n)
	for i in range(n-2):
		print(a[i],end=" ")
	print(a[-1],a[-2],sep=" ")
	exit()

fl=1
for i in range(n):
	if a[i]!=n-i:
		fl=0
if fl:
	for i in range(n-2):
		print(a[i],end=" ")
	print(a[-1],a[-2],sep=" ")
	print("0 "*n)
	exit()





d=[]
while ind>0 and a[ind]<a[ind-1]:
	d.append(a[ind])
	ind-=1
d.append(a[ind])
d.append(a[ind-1])
first=[]
for i in range(ind-1):
	first.append(a[i])

next=n
for i in d:
	if i>a[ind-1]:
		next=min(i,next)

first.append(next)
d.sort()
for i in d:
	if i!=next:
		first.append(i)







ind=n-1
d=[]
while ind>0 and a[ind-1]<a[ind]:
	d.append(a[ind])
	ind-=1

d.append(a[ind])
d.append(a[ind-1])

second=[]
for i in range(ind-1):
	second.append(a[i])

next=0
for i in d:
	if i<a[ind-1]:
		next=max(i,next)

second.append(next)
d.sort()
d.reverse()

for i in d:
	if i!=next:
		second.append(i)

print(*second)
print(*first)




