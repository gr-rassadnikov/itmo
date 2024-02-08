//import Foundation
//
//let k = Int(readLine()!)!
//let n = Int(readLine()!)!
//let a = readLine()!.split(separator: " ").map{Int($0)!}
//var dp = Array<Int>(repeating: 0, count: n)
//
//guard n != 0 else {
//    print(k)
//    exit(0)
//}
//
//dp[n - 1] = a[n - 1]
//
//for i in stride(from: n - 2, through: 0, by: -1) {
//    dp[i] = dp[i + 1] + a[i]
//}
//
//var ans = (n + 1) * k
//
//for i in stride(from: n - 1, through: 0, by: -1) {
//    ans = max(ans, k * (i + 1) + dp[i])
//}
//
//print(ans)
