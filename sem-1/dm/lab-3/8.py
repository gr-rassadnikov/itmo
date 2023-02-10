n, k = map(int, input().split())


def gen_1(g, n, was):
    if len(g) == k:
        for i in g:
            print(int(i) + 1, end=" ")
        print()
        return

    for i in range(was + 1, n):
        if g.count(str(i)) == 0:
            g.append(i)
            gen_1(g, n, i)
            g.pop()


a=[]
for i in range(n):
    a = []
    a.append(i)
    gen_1(a, n, i)
