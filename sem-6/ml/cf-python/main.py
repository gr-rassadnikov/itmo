from collections import defaultdict
from heapq import heappush, heappop

n, m, k = map(int, input().split())

a = [int(i) for i in input().split()]
classes = defaultdict(list)
partitions = [[] for _ in range(k)]
class_counters = [defaultdict(int) for _ in range(k)]

for i in range(n):
    classes[a[i]].append(i)

class_heap = []
for i in range(1, m+1):
    cnt = len(classes[i])
    if cnt > 0:
        for j in range(k):
            heappush(class_heap, (-cnt, j))

for i in range(n):
    cnt, part = heappop(class_heap)
    partitions[part].append(i)
    class_counters[part][classes[i][0]] += 1
    heappush(class_heap, (cnt + 1, part))

for part in range(k):
    for c, count in class_counters[part].items():
        if count > len(partitions[part]) // m:
            partitions[part] = [x for x in partitions[part] if x != c]
            for i in range(m):
                if len(partitions[i]) < len(partitions[part]) // m:
                    partitions[i].append(c)
                    break

for part in partitions:
    print(len(part), end=' ')
    for obj in part:
        print(obj + 1, end=' ')
    print()
