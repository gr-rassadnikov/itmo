////
////  C.swift
////  testYMeetup
////
////  Created by Grigorii Rassadnikov on 03.04.2023.
////
//
//import Foundation
//
//var p1 = readLine()!.split(separator: " ").map{Int($0)!}
//var n1 = p1.removeFirst()
//
//var p2 = readLine()!.split(separator: " ").map{Int($0)!}
//var n2 = p2.removeFirst()
//
//var p3 = readLine()!.split(separator: " ").map{Int($0)!}
//var n3 = p3.removeFirst()
//
//
//func get(p1 : [Int], p2 : [Int], p3 : [Int] ) -> [Int] {
//    let mrg = merge(s: p1, t: p2)
//    return merge(s: mrg, t: p3)
//}
//
//func merge(s : [Int], t: [Int]) -> [Int] {
//    let n = max(s.count, t.count)
//    var i = n
//    while i>0 {
//        let pref = s.suffix(i).prefix(t.count)
//        let suf = t.prefix(i)
//        if pref == suf {
//            return s + t.suffix(max(t.count - i, 0))
//        }
//        i-=1
//    }
//    return s + t
//}
//
//var result : [Int] = []
//var mn = n1 + n2 + n3 + 1
//let work = [get(p1: p1, p2: p2, p3: p3),
//            get(p1: p1, p2: p3, p3: p2),
//            get(p1: p2, p2: p1, p3: p3),
//            get(p1: p2, p2: p3, p3: p1),
//            get(p1: p3, p2: p1, p3: p2),
//            get(p1: p3, p2: p2, p3: p1),
//]
//
//for w in work {
//    if w.count < mn {
//        mn = w.count
//        result = w
//    }
//}
//print(mn)
//result.forEach{print($0, separator: " ", terminator: " " )}
//
//
//
