n=int(input())
def f(s,a,l):


    for i in range(l,a//2+1):
        if (a-i==0):
            f(s+str(i),a-i, i)

        elif a-i>0:
            f(s+str(i)+"+",a-i, i)

        else:
            return
    print(s, a, sep="")
    return

f("",n, 1)

