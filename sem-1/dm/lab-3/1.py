def gen_1(g,n):
    if (n==1):
        print(g)
        return
    gen_1(g+"0",n-1)
    gen_1(g+"1",n-1)

n=int(input())
gen_1("0", n)
gen_1("1",n)
