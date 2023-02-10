n, m = map(int, input().split())
a = [[0 for i in range(m)] for j in range(n)]
for i in range(n):
    a[i] = [int(i) for i in input().split()]

d = [[0 for i in range(m)] for j in range(n)]
d[0][0] = a[0][0]
for i in range(1, n):
    d[i][0] = a[i][0] + d[i - 1][0]

for i in range(1, m):
    d[0][i] = a[0][i] + d[0][i - 1]

for i in range(1, n):
    for j in range(1, m):
        d[i][j] = a[i][j] + max(d[i - 1][j], d[i][j - 1])



ans = ""
y = m - 1
x = n - 1


while (x != 0 or y != 0):

    if x > 0:
        if (d[x][y] == d[x - 1][y] + a[x][y]):
            x -= 1
            ans += ("D")
        else:
            y -= 1
            ans += ("R")
    else:
        y -= 1
        ans += ("R")
    if (x == 0 and y == 0):
        break

print(d[n - 1][m - 1])
print(ans[::-1], end="")

