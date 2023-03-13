//
//  G.swift
//  siriusTest
//
//  Created by Grigorii Rassadnikov on 19.02.2023.
//

import Foundation

func toBinary(from : Int, size: Int) -> [Bool] {
    var strArray = Array(String(from, radix: 2)).compactMap({$0 == "1"})
    var padding = Array(repeating: false, count: size - strArray.count)
    return padding + strArray
}

let n = readLine()!
let nArray : [Character] = Array(n)
let len = n.count
var max = 0
var maxResult = Array(repeating: false, count: n.count)

let toFor = Int(NSDecimalNumber(decimal: pow(2, n.count - 1)))

for i in 0..<toFor {
    let bin = toBinary(from: i, size: n.count)
//    print(bin)

    var set : Set<String> = Set()

    var add = ""
    var cnt = 0
    var can = true

    for j in 0..<len {
        if !bin[j] {
            add+=String(nArray[j])
        } else {
            if set.contains(add) || add.count > 1 && add[add.index(add.startIndex, offsetBy: 0)] == "0"  {
                can = false
                break
            }
            set.insert(add)
            cnt+=1
            add=String(nArray[j])
        }
    }
    if set.contains(add) || add.count > 1 && add[add.index(add.startIndex, offsetBy: 0)] == "0"  {
        can = false
    }else {
        set.insert(add)
        cnt+=1
    }

    if can {
        if cnt > max {
            max = cnt
            maxResult = bin
        }
    }

}

for i in 0..<len {
    if maxResult[i] {
        print("-", terminator: "")
    }
    print(nArray[i], terminator: "")
}
