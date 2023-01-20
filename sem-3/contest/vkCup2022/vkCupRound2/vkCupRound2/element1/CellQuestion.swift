//
//  CellQuestion.swift
//  vkCupRound2
//
//  Created by Grigorii Rassadnikov on 16.01.2023.
//

import Foundation
import UIKit

class CellQuestion: UITableViewCell {
    
    @IBOutlet weak var view: UIView!
    
    
    private lazy var titleLabel: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.text = "Quetion ?/?"
        label.numberOfLines = 0
        label.textColor = .white
        return label
    }()

    private var question: Question?
    
    private lazy var tableView: UITableView = {
        let table = UITableView()
        table.translatesAutoresizingMaskIntoConstraints = false
        table.backgroundColor = .green
        return table
    }()
    
    public func setup(with question : Question) {
        self.question = question
        
        tableView.dataSource = self
        tableView.delegate = self
        tableView.register(UINib(nibName: "CellQuestion", bundle: nil), forCellReuseIdentifier: "CellQuestion")
        tableView.reloadSectionIndexTitles()
        
        view.backgroundColor = .blue
        view.addSubview(titleLabel)
        view.addSubview(tableView)
    
        

        NSLayoutConstraint.activate([
            titleLabel.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 6),
            titleLabel.widthAnchor.constraint(equalToConstant: 200),
            titleLabel.topAnchor.constraint(equalTo: view.topAnchor, constant: 6),
            titleLabel.heightAnchor.constraint(equalToConstant: 40),
//            titleLabel.topAnchor.constraint(equalTo: view.topAnchor, constant: 16),
//            titleLabel.bottomAnchor.constraint(equalTo: view.bottomAnchor, constant: -160),
//            titleLabel.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
//            titleLabel.trailingAnchor.constraint(equalTo: view.leadingAnchor, constant: -16),
            
            tableView.topAnchor.constraint(equalTo: titleLabel.bottomAnchor, constant: 20),
            tableView.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: -120),
            tableView.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 4),
            tableView.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -4),

        ])
    }

}

extension CellQuestion: UITableViewDelegate, UITableViewDataSource {
    func tableView(_: UITableView, numberOfRowsInSection _: Int) -> Int {
        return question?.answers.count ?? 1
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        guard let cell = tableView.dequeueReusableCell(withIdentifier: "CellAnswer") as? CellAnswer else {
            return UITableViewCell()
        }
        cell.setup(with: question?.answers[indexPath.item])
        print("++++++++++++++++++++")
        return cell
    }

    func numberOfSections(in _: UITableView) -> Int {
        return 1
    }

    func tableView(_: UITableView, heightForRowAt _: IndexPath) -> CGFloat {
        return UITableView.automaticDimension
    }
}
