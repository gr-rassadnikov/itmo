//
//  siriusIlTests.swift
//  siriusIlTests
//
//  Created by Grigorii Rassadnikov on 12.02.2023.
//

import XCTest
@testable import siriusIl

final class siriusIlTests: XCTestCase {

    func testTaskI() {
        
        var p : [Int] = (readLine()?.split(separator: " ").map({(Int($0) ?? -1)-1}))!
        
        for i in p {
            print(i)
        }
        
        
        
        
    }

}
