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

first = ""
second = ""

i = n
j = m
source = 3
while i > 0 or j > 0:
    if source == 1:
        first = s[i - 1] + first
        second = "-" + second
        if upper[i][j] == upper[i - 1][j] + q:
            source = 1
        else:
            source = 3
        i -= 1
    elif source == 2:
        first = "-" + first
        second = t[j - 1] + second
        if lower[i][j] == lower[i][j - 1] + q:
            source = 2
        else:
            source = 3
        j -= 1
    elif source == 3:
        if i > 0 and j > 0 and \
                (mainnn[i][j] == mainnn[i - 1][j - 1] + (1 if s[i - 1] == t[j - 1] else -1)):
            first = s[i - 1] + first
            second = t[j - 1] + second
            i -= 1
            j -= 1
            source = 3
        elif j > 0 and i >= 0 and mainnn[i][j] == lower[i][j]:
            first = "-" + first
            second = t[j - 1] + second
            if lower[i][j] == lower[i][j - 1] + q:
                source = 2
            else:
                source = 3
            j -= 1
        elif i > 0 and j >= 0 and mainnn[i][j] == upper[i][j]:
            first = s[i - 1] + first
            second = "-" + second
            if upper[i][j] == upper[i - 1][j] + q:
                source = 1
            else:
                source = 3
            i -= 1

print(first)
print(second)
