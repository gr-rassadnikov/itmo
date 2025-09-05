_m = 1
_u = -1
_d = -2

s = input()
t = input()

swapper = False

# if len(s) < len(t):
#     c = s
#     s = t
#     t = c
#     swapper = True

n = len(s)
m = len(t)

dp = [[0 for i in range(m + 1)] for j in range(n + 1)]

for i in range(1, n + 1):
    dp[i][0] = _d * i

for j in range(1, m + 1):
    dp[0][j] = _d * j

first = ""
second = ""

for i in range(1, n + 1):
    for j in range(1, m + 1):
        hit = dp[i - 1][j - 1] + (_m if s[i - 1] == t[j - 1] else _u)
        deletion = dp[i][j - 1] + _d
        insertion = dp[i - 1][j] + _d
        dp[i][j] = max(hit, deletion, insertion)

i = n
j = m
while i > 0 or j > 0:
    if i > 0 and j >= 0 and dp[i][j] == dp[i - 1][j] + _d:
        first = s[i - 1] + first
        second = "-" + second
        i -= 1
    elif j > 0 and i >= 0 and dp[i][j] == dp[i][j-1] + _d:
        first = "-" + first
        second = t[j - 1] + second
        j -= 1
    elif i > 0 and j > 0 and \
            (dp[i][j] == dp[i - 1][j - 1] + _m or dp[i][j] == dp[i - 1][j - 1] + _u):
        first = s[i - 1] + first
        second = t[j - 1] + second
        i -= 1
        j -= 1

print(first)
print(second)
