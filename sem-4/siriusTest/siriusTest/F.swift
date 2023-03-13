//
//  F.swift
//  siriusTest
//
//  Created by Grigorii Rassadnikov on 19.02.2023.
//


let n = Int(readLine() ?? "0")!
let s = readLine()!
let str : [Character] = Array(s)

for t in 1...n {
    var yes =  true
    var arr = Array(repeating: Character("#"), count: t)
    for i in 0..<s.count {
        if str[i] == "#" {
            continue
        } else {
            if arr[i%t] == "#" {
                arr[i%t] = str[i]
            } else if arr[i%t] != str[i] {
                yes = false
                break
            }
        }
    }
    if yes {
        print(t)
        break
    }
}
