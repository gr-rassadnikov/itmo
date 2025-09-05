match_score = 2
mismatch_score = -1
gap_penalty = -2

def lazy_needleman_wunsch(s, t):
    _m = match_score
    _u = mismatch_score
    _d = gap_penalty
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
        elif j > 0 and i >= 0 and dp[i][j] == dp[i][j - 1] + _d:
            first = "-" + first
            second = t[j - 1] + second
            j -= 1
        elif i > 0 and j > 0 and \
                (dp[i][j] == dp[i - 1][j - 1] + _m or dp[i][j] == dp[i - 1][j - 1] + _u):
            first = s[i - 1] + first
            second = t[j - 1] + second
            i -= 1
            j -= 1

    return (first, second)


def needleman_wunsch(s, t):
    n = len(s)
    m = len(t)
    dp = [[0] * (m + 1) for _ in range(2)]

    for j in range(1, m + 1):
        dp[0][j] = dp[0][j - 1] + gap_penalty

    for i in range(1, n + 1):
        dp[1][0] = dp[0][0] + gap_penalty
        for j in range(1, m + 1):
            match = dp[0][j - 1] + (match_score if s[i - 1] == t[j - 1] else mismatch_score)
            delete_s = dp[0][j] + gap_penalty
            delete_t = dp[1][j - 1] + gap_penalty
            dp[1][j] = max(match, delete_s, delete_t)

        dp[0] = dp[1][:]

    return dp[1]


def hirschberg(s, t):
    n = len(s)
    m = len(t)
    if n == 0:
        return ("-" * m, t)
    if m == 0:
        return (s, "-" * n)
    if n == 1 or m == 1:
        return lazy_needleman_wunsch(s, t)
    else:
        xmid = n // 2

        left = needleman_wunsch(s[:xmid], t)
        right = needleman_wunsch(s[xmid:][::-1], t[::-1])[::-1]

        max_score = -1
        ymid = 0
        for i in range(m + 1):
            score = left[i] + right[i]
            if score >= max_score:
                max_score = score
                ymid = i

        opt1 = hirschberg(s[:xmid], t[:ymid])
        opt2 = hirschberg(s[xmid:], t[ymid:])

        # print(opt1)
        # print(opt2)
        return opt1[0] + opt2[0], opt1[1] + opt2[1]


s = input()
t = input()
l, r = hirschberg(s, t)

print(l)
print(r)