//import Foundation
//
//let n = Int(readLine()!)!
//var cntGood = 0.0
//var cntBad = 0.0
//var isStart = Array<Bool>(repeating: false, count: 1_000_000 + 1)
//for _ in 0..<n {
//    let s = readLine()!
//    let uid = Int(readLine()!)!
//    if s == "APPLICATION_FINISHED_LAUNCHING" {
//        if (isStart[uid]) {
//            cntBad += 1
//        }
//        isStart[uid] = true
//    } else if s == "APPLICATION_TERMINATED" {
//        if isStart[uid] {
//            isStart[uid] = false
//            cntGood += 1
//        }else {
//            cntBad += 1
//        }
//    }
//
//}
//
//for e in isStart {
//    if e {
//        cntBad += 1
//    }
//}
//
//let ans  = cntBad / (cntGood + cntBad)
//print(ans * 100)
