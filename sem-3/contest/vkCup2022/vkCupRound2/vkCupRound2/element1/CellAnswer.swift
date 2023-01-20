//
//  CellAnswer.swift
//  vkCupRound2
//
//  Created by Grigorii Rassadnikov on 16.01.2023.
//

import Foundation
import UIKit

class CellAnswer: UITableViewCell {
    
    @IBOutlet weak var view: UIView!
    
    private lazy var answer: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.text = "............"
        return label
    }()
    
    private lazy var tableView: UITableView = {
        let table = UITableView()
        table.translatesAutoresizingMaskIntoConstraints = false
        table.backgroundColor = .green
        return table
    }()
    
    public func setup(with answer : String?) {
        self.answer.text = answer
        view.addSubview(self.answer)
        
        view.backgroundColor = .red

        NSLayoutConstraint.activate([
            self.answer.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 6),
            self.answer.widthAnchor.constraint(equalToConstant: 200),
            self.answer.topAnchor.constraint(equalTo: view.topAnchor, constant: 6),
            self.answer.heightAnchor.constraint(equalToConstant: 40),
        ])
    }

}
