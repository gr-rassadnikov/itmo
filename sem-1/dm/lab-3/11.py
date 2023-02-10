
n=int(input())
gl=n
s=[]
def gen_1(g,n):
    if (n==1):
        a=[]
        num=1
        for i in range(gl-1,-1,-1):
            if g[i]=="1":
                a.append(num)
            num+=1
        s.append(a)

        return
    gen_1(g+"0",n-1)
    gen_1(g+"1",n-1)

gen_1("0", n)
gen_1("1",n)
s.sort()
for i in s:
    print(*i)