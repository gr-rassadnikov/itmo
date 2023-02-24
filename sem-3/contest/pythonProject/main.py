A, B, C = [input() for _ in range(3)]


def spl(s):
    q = s.split(":")
    w = int(q[0]) * 60 * 60
    w += int(q[1]) * 60
    w += int(q[2])
    return w


def make(s):
    to = ""
    s = int(s)
    r1 = str((s // (60 * 60))%24)
    if len(r1) == 1:
        r1 = "0" + r1
    r2 = str((s // 60) % 60)
    if len(r2) == 1:
        r2 = "0" + r2
    r3 = str(s % 60)
    if len(r3) == 1:
        r3 = "0" + r3
    to=r1+":"+r2+":"+r3

    return to


a = spl(A)
b = spl(B)
c = spl(C)
if c < a:
    c += 60 * 60 * 24

t = b + ((c - a)+1) // 2

print(make(t))

# 15:01:00
# 18:09:45
# 15:01:40

# 23:58:10
# 00:01:17
# 00:00:01
#
# 00:00:00
# 23:59:01
# 00:00:50
#
# 15:01:00
# 18:09:45
# 14:01:40
#
# 01:00:00
# 23:59:01
# 23:00:50
