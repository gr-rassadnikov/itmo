//
//  Page.swift
//  ios-itmo-2022-assignment2
//
//  Created by Grigorii Rassadnikov on 26.10.2022.
//

import UIKit

class Page: NSObject {
    public var author: String
    public var name: String
    public var date: String
    public var cnt: Int
    public var imagePath: String
    public var image: UIImage?
    public var movieId: Int

    init(author: String = "", name: String = "", date: String = "", cnt: Int = 0, imagePath: String = "", image: UIImage? = nil, movieId: Int) {
        self.author = author
        self.name = name
        self.date = date
        self.cnt = cnt
        self.image = image
        self.imagePath = imagePath
        self.movieId = movieId
    }
}

extension Page {
    static func < (lhs: Page, rhs: Page) -> Bool {
        let lhsArr: [String] = lhs.date.components(separatedBy: ["."])
        let rhsArr: [String] = rhs.date.components(separatedBy: ["."])
        guard let lhsInt = Int(lhsArr[0]) else { return false }
        guard let rhsInt = Int(rhsArr[0]) else { return false }
        return lhsInt < rhsInt
    }

    override public var description: String {
        return "\n{\n author: \(author),\n"
            + " name: \(name),\n"
            + " date: \(date),\n"
            + " cnt: \(cnt),\n"
            + " imageName: \(image ?? UIImage()),\n"
    }

    public func getYear() -> Int {
        let arr = date.components(separatedBy: ["."])
        if arr.count == 1 {
            return Int(arr[0]) ?? 0
        } else {
            return Int(arr[2]) ?? 0
        }
    }
}

public func toYear(date: String) -> Int {
    return Int(date.components(separatedBy: ["."])[2]) ?? 0
}
