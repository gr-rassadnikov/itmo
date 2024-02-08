//
//  main.swift
//  shmrTest
//
//  Created by Grigorii Rassadnikov on 25.04.2023.
//

import Foundation

//import Foundation
//
//print("Hello, World!")
//
//
// Task 1 -------------------
//func foo() {
//    print("A")
//    assert(Thread.isMainThread)
//
//    DispatchQueue.main.sync {
//        assert(Thread.isMainThread)
//        print("B")
//
//        DispatchQueue.main.async {
//            assert(Thread.isMainThread)
//            print("C")
//
//            DispatchQueue.main.async {
//                assert(Thread.isMainThread)
//                print("D")
//            }
//        }
//
//        DispatchQueue.global().sync {
//            print("E")
//
//            DispatchQueue.main.async {
//                assert(Thread.isMainThread)
//                print("F")
//            }
//        }
//
//        print("G")
//    }
//
//    print("H")
//}
//
//foo()
//
//for _ in 0...10000 {
//
//}
//
//func readFile(filepath: String) throws {
//    let file = open(filepath)
//
//    defer {
//        close(file)
//    }
//    let date = try read(file)
//    print(date)
//}

//import Foundation
//
//print(readLine()!.split(separator: " ").map{Int64($0)!}.sorted()[1])
//


//import Foundation
//
//let n = Int(readLine()!)!
//
//var cntApl = 0.0
//var cntF = 0.0
//for _ in 0..<n {
//    let s = readLine()!
//    let _ = Int(readLine()!)!
//    if s == "APPLICATION_FINISHED_LAUNCHING" {
//        cntApl += 1
//    } else if s == "APPLICATION_TERMINATED" {
//        cntF += 1
//    }
//
//}
//
//let ans  = 1 - cntF / cntApl
//print(ans * 100)

//for i in 0...10000 {
//    for j in 0...10000 {
//        if abs(100*Double(i)/Double(j) - 3.4170053) < 0.000001 {
//            print(i)
//            print(j)
//        }
//    }
//}

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



//import Foundation
//
//let n = Int(readLine()!)!
//let a = readLine()!.split(separator: " ").map{Int64($0)!}
//let b = readLine()!.split(separator: " ").map{Int64($0)!}
//
//var d : [Int64 : Int64] = [0: Int64(n-1)]
//
//var aSum: Int64 = 0
//var bSum: Int64 = 0
//
//var aS = Array<Int64>(repeating: 0, count: n)
//var bS = Array<Int64>(repeating: 0, count: n)
//
//
//for i in stride(from: n - 1, through: 0, by: -1) {
//    aSum += a[i]
//    bSum += b[i]
//    let dur = aSum - bSum
//    if let _ = d[dur] {
//
//    } else {
//        d[dur] = Int64(i)
//    }
//    aS[i] = aSum
//    bS[i] = bSum
//}
//
//var mx: Int64 = -1
//for ind in 0..<n {
//    if let val = d[aS[ind] - bS[ind]] {
//        if val == ind {
//            continue
//        }
//        if mx < val - Int64(ind) {
//            mx = val - Int64(ind) - 1
//        }
//    }
//}
//
//if aS[0] == bS[0] {
//    mx = Int64(n - 1)
//}
//
//print(mx)
//


//swift 2.2

//struct Player{
//    let name: String
//    var level: Int
//}
//
//extension Player {
//    mutating func increaseLevel() {
//        level += 1
//    }
//}


//swift 2.3
//class Player {
//    var name: String
//    init(name: String) {
//        self.name = name
//    }
//}
//
//struct PlayerQueue {
//    var players: [Player]
//
//    init(players: [Player]) {
//        self.players = players
//    }
//}
    
//extension Array where Element == Player  {
//    var allPlayersName: String {
//        return reduce("") {"\($0) \($1.name )"}
//    }
//}
//
//let queue = PlayerQueue(
//    players:[
//        Player (name: "A"),
//        Player (name: "B"),
//        Player (name: "C")
//    ]
//)
//var copy = queue
//queue.players.last!.name = copy.players.removeLast().name == "C" ? "D" : queue.players.last!.name
//
//print (queue.players.allPlayersName) // A B D
//print (copy.players.allPlayersName) // A B

protocol Loader {
    func load(completion: @escaping (Data) -> ())
}
final class Worker {
    private let loader: Loader
    init(loader: Loader) {
        self.loader = loader
    }
    
    func doTheJob( ) {
        loader.load {  data in // [1]
            DispatchQueue.main.async {  // [2]
                self?.onJobDone(with: data)
            }
        }
    }
    
    func onJobDone(with data: Data) {
    }
}

//let w = Worker(loa)
//w.doTheJob()
