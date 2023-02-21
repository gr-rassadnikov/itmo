//
//  main.swift
//  siriusTest
//
//  Created by Grigorii Rassadnikov on 19.02.2023.
//


import Foundation

let n = Int(readLine()!)!

let parents : [Int] = (readLine()?.split(separator: " ").map({ Int($0)! }))!

var graph : [[Int]] = Array(repeating: [], count: n)

var answer = Array(repeating: 0, count: n)

for i in 0..<n {
    if parents[i] != 0 {
        graph[parents[i] - 1].append(i)
    }
}

func dfs(node : Int, level : Int) {
    answer[node] = level
    for to in graph[node] {
        dfs(node: to, level: level + 1)
    }
}

let root = parents.firstIndex(of: 0) ?? 0

dfs(node: root, level: 0)

for i in answer {
    print(i, terminator: " ")
}
