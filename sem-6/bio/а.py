alphabet = ['A', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'Y']
masses = [71, 103, 115, 129, 147, 57, 137, 113, 128, 113, 131, 114, 97, 128, 156, 87, 101, 99, 186, 163]

toNumber = dict(zip(alphabet, masses))
toCHR = dict(zip(masses, alphabet))


def graph(s):
    g = [[] for i in range(len(s))]
    for i in range(len(s)):
        for j in range(len(s)):
            n = s[j] - s[i]
            if n in masses:
                g[i].append([j, toCHR[n]])
    return g


# base_spectrum = [int(i) for i in input().split()]
# end = len(base_spectrum) - 1
# g = graph(base_spectrum)
# BIGGEST = base_spectrum[-1]


def ideal(peptide):
    spectrum = []
    last = 0
    for i in peptide:
        last += toNumber[i]
        spectrum.append(last)
    reverse = []
    last = spectrum[-1]
    for i in peptide:
        last -= toNumber[i]
        reverse.append(last)

    # print(reverse)
    # print(spectrum)
    ans = reverse + spectrum
    ans.sort()

    # print(ans)
    return list(dict.fromkeys(ans))


peptide = input()
print(*ideal(peptide))
# 0 57 114 128 215 229 316 330 387 444
