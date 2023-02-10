def gen_1(g,n, was):
    if (len(g)==n):
        for i in g:
            print(int (i)+1, end=" ")
        print()
        return

    for i in range(n):
        if (g.count(str(i))==0):
            gen_1(g+str(i), n, was+str(i))


n=int(input())
for i in range(n):
    gen_1(str(i), n, str(i))
