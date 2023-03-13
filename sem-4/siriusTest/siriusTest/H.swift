//
//  main.swift
//  siriusTest
//
//  Created by Grigorii Rassadnikov on 19.02.2023.
//



let s = readLine()!

var st : Set<String> = Set(arrayLiteral: "")

var add = ""

for i in s {
    if st.contains(add) {
        add+=String(i)
    } else {
        st.insert(add)
        print(add, terminator: " ")
        add = String(i)
    }
}
print(add)

