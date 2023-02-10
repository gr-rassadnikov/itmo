n = int(input())
def gen_1( a, how, j):
    if j == n * 2:
        print(*a, sep='')
        return
    else:
        if how + j == 2 * n:
            a[j] = ')'
            how -= 1
            gen_1(a, how, j + 1)
        else:
            how += 1
            a[j] = '('
            gen_1( a, how, j + 1);
            if how!=1 and how:
                a[j] = ')'
                how -= 2
                gen_1( a, how, j + 1)


gen_1([0] * (2 * n), 0, 0)
