//
//  Question.swift
//  vkCupRound2
//
//  Created by Grigorii Rassadnikov on 15.01.2023.
//

import Foundation

class Question {
    var title : String
    var answers : [String]
    var trueAnswer : Int
    var stat : [Int] = []
    var summGet : Int = 0
    
    init(title: String, answers: [String], trueAnswer: Int) {
        self.title = title
        self.answers = answers
        self.trueAnswer = trueAnswer
        stat = []
    }
}
