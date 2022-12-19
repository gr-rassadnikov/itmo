//
//  activity.swift
//  mobile
//
//  Created by Grigorii Rassadnikov on 18.12.2022.
//

import Foundation

struct Activity {
    var name: String
    var isChoosen = false

    init(name: String, isChoosen: Bool = false) {
        self.name = name
        self.isChoosen = isChoosen
    }
}
