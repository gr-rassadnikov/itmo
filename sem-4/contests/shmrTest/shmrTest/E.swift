//import Foundation
//
//let n = Int(readLine()!)!
//let a = readLine()!.split(separator: " ").map{Int($0)!}
//let b = readLine()!.split(separator: " ").map{Int($0)!}
//
//var d : [Int : Int] = [:]
//
//var aSum = 0
//var bSum = 0
//
//var aS = Array<Int>(repeating: 0, count: n)
//var bS = Array<Int>(repeating: 0, count: n)
//
//
//for i in stride(from: n - 1, through: 0, by: -1) {
//    aSum += a[i]
//    bSum += b[i]
//    let dur = aSum - bSum
//    if let _ = d[dur] {
//
//    } else {
//        d[dur] = i
//    }
//    aS[i] = aSum
//    bS[i] = bSum
//}
//
//var mx = -1
//var i = -1
//var j = -1
//for ind in 0..<n {
//    if let val = d[aS[ind] - bS[ind]] {
//        if val == ind {
//            continue
//        }
//        if mx < val - ind {
//            mx = val - ind
//            i = ind
//            j = val
//        }
//    }
//}
//
//if aS[0] == bS[0] {
//    mx = n - 1
//}
//
//print(mx)
//
