//
//  TESTSWIFTTests.swift
//  TESTSWIFTTests
//
//  Created by Grigorii Rassadnikov on 21.12.2022.
//

import XCTest
@testable import TESTSWIFT

final class TESTSWIFTTests: XCTestCase {
    
    func testT(){
        
       
        class VideoMode {
          var interlaced = false
          var frameRate = 0.0
          var name: String?
        }
        let tenEighty = VideoMode()
        tenEighty.interlaced = true
        tenEighty.name = "1080i"
        tenEighty.frameRate = 25.0
        let alsoTenEighty = tenEighty
        alsoTenEighty.frameRate = 30.0
        print("The frameRate property of tenEighty is now \
        (tenEighty.frameRate)")
            
            
            
            
            
            
            
            
            

        
    }
}
