s = input()
n = len(s)
dp = [[0 for i in range(n)] for j in range(n)]


def isRebro(a, b):
    if a == 'A' and b == 'U' or \
            a == 'U' and b == 'A' or \
            a == 'G' and b == 'C' or \
            a == 'C' and b == 'G':
        return 1
    return 0


for t in range(2, n):
    for i in range(n - t):
        j = i + t
        dp[i][j] = max(dp[i + 1][j], dp[i][j - 1])
        dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + isRebro(s[i], s[j]))
        for k in range(i, j):
            dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j])


# for i in dp:
#     print(*i)
# print(dp[0][n - 1])


def print_seq(s, dp, i, j):
    if i > j or i == n - 1 or j == 0:
        return ""
    if dp[i][j] == dp[i + 1][j]:
        return "." + print_seq(s, dp, i + 1, j)
    if dp[i][j] == dp[i][j - 1]:
        return print_seq(s, dp, i, j - 1) + "."
    if dp[i][j] == dp[i + 1][j - 1] + isRebro(s[i], s[j]):
        return "(" + print_seq(s, dp, i + 1, j - 1) + ")"

    for k in range(i + 1, j):
        if dp[i][j] == dp[i][k] + dp[k + 1][j]:
            return print_seq(s, dp, i, k) + print_seq(s, dp, k + 1, j)


print(print_seq(s, dp, 0, n - 1))
