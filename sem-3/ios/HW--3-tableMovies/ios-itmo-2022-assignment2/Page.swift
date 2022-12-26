//
//  Page.swift
//  ios-itmo-2022-assignment2
//
//  Created by Grigorii Rassadnikov on 26.10.2022.
//

import UIKit

class Page {
    public var author: String
    public var name: String
    public var date: String
    public var cnt: Int
    public var year : Int

    init(author: String = "", name: String = "", date: String = "", cnt: Int = 0) {
        self.author = author
        self.name = name
        self.date = date
        self.cnt = cnt
        self.year = Int(self.date.components(separatedBy: ["."])[2])
    }
    
    public func getYear() -> Int {
        let intArr: [String] = self.date.components(separatedBy: ["."])
        return Int(intArr[2])
    }
}

extension Page {
    static func < (lhs: Page, rhs: Page) -> Bool {
        let lhsArr: [String] = lhs.date.components(separatedBy: ["."])
        let rhsArr: [String] = rhs.date.components(separatedBy: ["."])
        guard let lhsInt = Int(lhsArr[2]) else { return false }
        guard let rhsInt = Int(rhsArr[2]) else { return false }
        return lhsInt < rhsInt
    }

    override public var description: String {
        return "\n{\n author: \(author),\n"
            + " name: \(name),\n"
            + " date: \(date),\n"
            + " cnt: \(cnt),\n"
    }
    
}
