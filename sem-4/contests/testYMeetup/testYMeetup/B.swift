////
////  B.swift
////  testYMeetup
////
////  Created by Grigorii Rassadnikov on 03.04.2023.
////
//
//import Foundation
//
//let arr = readLine()!.split(separator: " ").map{Int($0)!}
//let n = arr[0]
//let m = arr[1]
//
//var isOut = Array(repeating: false, count: n)
//var cntIn = Array(repeating: Set<Int>(), count: n)
//
//for _ in 0..<m {
//    let ar = readLine()!.split(separator: " ").map{Int($0)!}
//    let from = ar[0] - 1
//    let to = ar[1] - 1
//    if to != from {
//        isOut[from] = true
//        cntIn[to].insert(from)
//    }
//}
//
//func work() -> Int {
//    for i in 0..<n {
//        if !isOut[i] && (cntIn[i].count == n - 1) {
//            return i + 1
//        }
//    }
//    return -1
//}
//
//print(work())
