a=[[[ 0 for i2 in range(3)]for ij in range(3)]for i in range(3)]
for k in range(3):
    for i in range(3):
            c=[int(f) for f in input().split()]
            for j in range(3):
                a[k][i][j]=c[j]
for i in range(3):
    for j in range(3):
        for k in range(3):
            print(a[i][j][k],end=" ")

    print()

print()

b=[[[ 0 for i2 in range(3)]for ij in range(3)]for i in range(3)]
for i in range(3):
    for j in range(3):
        for k in range(3):
            b[i][j][k]=a[i][j][k]+a[i][k][j]+a[j][i][k]+a[j][k][i]+a[k][j][i]+a[k][i][j]

for i in range(3):
    for j in range(3):
        for k in range(3):
            print(b[i][j][k],end=" ")

    print()

print()

c=[[[ 0 for i2 in range(3)]for ij in range(3)]for i in range(3)]
for i in range(3):
    for j in range(3):
        for k in range(3):
            c[i][j][k]=a[i][j][k]-a[i][k][j]-a[j][i][k]+a[j][k][i]-a[k][j][i]+a[k][i][j]

for i in range(3):
    for j in range(3):
        for k in range(3):
            print(-c[i][j][k],end=" ")

    print()


print()

d=[[[ 0 for i2 in range(3)]for ij in range(3)]for i in range(3)]
for i in range(3):
    for j in range(3):
        for k in range(3):
            d[i][j][k]=a[i][j][k]+a[j][i][k]

for i in range(3):
    for j in range(3):
        for k in range(3):
            print(d[i][j][k],end=" ")

    print()



print()

e=[[[ 0 for i2 in range(3)]for ij in range(3)]for i in range(3)]
for i in range(3):
    for j in range(3):
        for k in range(3):
            e[i][j][k]=a[i][j][k]-a[k][j][i]

for j in range(3):
    for i in range(3):
        for k in range(3):
            print(e[i][j][k],end=" ")

    print()
