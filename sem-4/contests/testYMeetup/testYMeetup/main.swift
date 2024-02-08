extension Array where Element: Comparable {
    func upper_bound(key: Element) -> Int{
        var l = -1
        var r = self.count
        while l < r - 1 {
            var m = (l + r) / 2
            if self[m] < key {
                l = m
            }
            else {
                r = m
            }
        }
        return r
    }

    func lower_bound(key: Element) -> Int{
        var l = -1
        var r = self.count
        while l < r - 1 {
            var m = (l + r) / 2
            if self[m] <= key {
                l = m
            }
            else {
                r = m
            }
        }
        return l
    }
}

let arr: [Int] = readLine()!.split(separator: " ").map{Int($0)!}
let n = arr[0]
let m = arr[1]

var line : [[Int]] = Array(repeating: [], count: n)
var lineCount : [[Int]] = Array(repeating: [], count: n)

var row : [[Int]] = Array(repeating: [], count: m)
var rowCount : [[Int]] = Array(repeating: [], count: m)

var data: [[Character]] = Array(repeating: [], count: n)

for i in 0..<n {
    let str: [Character] = Array(readLine()!)
    data[i] = str
}

var check: [(Int, Int)] = []

for i in 0..<n {
    var lastCount = 0
    line[i].append(0)
    lineCount[i].append(0)
    for j in 0..<m {
        if data[i][j] == "B" {
            lastCount += 1
        } else if data[i][j] == "W" {
            line[i].append(j)
            lineCount[i].append(lastCount)
        } else {
            check.append((i, j))
        }
    }
    line[i].append(m)
    lineCount[i].append(lastCount)
}

for i in 0..<m {
    var lastCount = 0
    row[i].append(0)
    rowCount[i].append(0)
    for j in 0..<n {
        if data[j][i] == "B" {
            lastCount += 1
        } else if data[j][i] == "W" {
            row[i].append(j)
            rowCount[i].append(lastCount)
        }
    }
    row[i].append(n)
    rowCount[i].append(lastCount)
}

var ans = 0
var result = (0, 0)

for (i, j) in check {
    let w = line[i].lower_bound(key: j)
    let e = line[i].upper_bound(key: j)
    let n = row[j].lower_bound(key: i)
    let s = row[j].upper_bound(key: i)
    let local = gg(lineCount[i], e) - gg(lineCount[i], w) + gg(rowCount[j], s) - gg(rowCount[j], n)
    if local > ans {
        ans = local
        result = (i, j)
    }

}

func gg(_ a: [Int], _ ind: Int) -> Int{
    if ind == -1 || a.count == 0{
        return 0
    }
    if ind >= a.count {
        return a[a.count - 1]
    }
    return a[ind]
}

print("\(result.0+1) \(result.1+1)")
//3 3
//WBW
//B.W
//.BW
