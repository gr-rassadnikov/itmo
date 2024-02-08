//import Foundation
//
//let n = Int(readLine()!)!
//let a = readLine()!.split(separator: " ").map{Int($0)!}
//
//func sn(_ n: Int) -> Int64 {
//    guard n != 1 else {
//        return 1
//    }
//    return Int64(n) * Int64(n + 1) / 2
//}
//var summ: Int64 = 0
//var countOne = 0
//var last = 0
//for i in 0..<n {
//    if a[i] == 1 {
//        summ += sn(i - last)
//        last = i + 1
//        countOne += 1
//    }
//}
//guard countOne != n else {
//    print(sn(n))
//    exit(0)
//}
//print(summ + sn(n - last))
