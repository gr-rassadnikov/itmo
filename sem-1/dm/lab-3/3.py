def gen_3(g,n):
    if (n==1):
        print(g)
        s2="";
        for i in g:
            s2+=str((int(i)+1)%3)
        print(s2)
        s2 = "";
        for i in g:
            s2 += str((int(i) + 2) % 3)
        print(s2)
        return
    gen_3(g+"0",n-1)
    gen_3(g+"1",n-1)
    gen_3(g + "2", n - 1)

n=int(input())
gen_3("0", n)
