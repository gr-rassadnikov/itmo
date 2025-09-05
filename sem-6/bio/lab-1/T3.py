_m = 1
_u = -1
inf = 1e9

s = input()
t = input()

p, q = map(int, input().split())

n = len(s)
m = len(t)

upper = [[-inf for i in range(m + 1)] for j in range(n + 1)]
lower = [[-inf for i in range(m + 1)] for j in range(n + 1)]
mainnn = [[0 for i in range(m + 1)] for j in range(n + 1)]

for i in range(1, n + 1):
    upper[i][0] = q * i + p
    mainnn[i][0] = q * i + p

for j in range(1, m + 1):
    lower[0][j] = q * j + p
    mainnn[0][j] = q * j + p

for i in range(1, n + 1):
    for j in range(1, m + 1):
        upper[i][j] = max(
            upper[i - 1][j] + q,
            mainnn[i - 1][j] + p + q
        )

        lower[i][j] = max(
            lower[i][j - 1] + q,
            mainnn[i][j - 1] + p + q
        )

        mainnn[i][j] = max(
            mainnn[i - 1][j - 1] + (1 if s[i - 1] == t[j - 1] else -1),
            upper[i][j],
            lower[i][j]
        )

print(mainnn[n][m])
