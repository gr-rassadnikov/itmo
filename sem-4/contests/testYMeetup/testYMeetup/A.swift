////
////  A.swift
////  testYMeetup
////
////  Created by Grigorii Rassadnikov on 03.04.2023.
////
//
//import Foundation
//
//let N = 10_000 + 1
//let n : Int = Int(readLine()!)!
//var a : [Int] = readLine()!.split(separator: " ").map{Int($0)!}
//a.sort()
//
//let k = Int(readLine()!)!
//var counter = Array(repeating: 0, count: N)
//
//for _ in 0..<k {
//    let f = readLine()!.split(separator: " ").map{Int($0)!}
//    let w = f[0]
//    let cnt = f[1]
//    counter[w]+=cnt
//}
//
//var indIntCout = 0
//
//for w in a {
//    indIntCout = max(indIntCout, w)
//    if indIntCout >= N {
//        print("No")
//        exit(0)
//    }
//    while indIntCout < N && counter[indIntCout] == 0 {
//        indIntCout+=1
//    }
//    if indIntCout < N {
//        counter[indIntCout]-=1
//    } else {
//        print("No")
//        exit(0)
//    }
//}
//print("Yes")
