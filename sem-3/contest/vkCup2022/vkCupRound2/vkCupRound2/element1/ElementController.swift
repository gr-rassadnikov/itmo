//
//  ViewController.swift
//  vkCupRound2
//
//  Created by Grigorii Rassadnikov on 15.01.2023.
//

import Foundation
import UIKit


class ElementController: UIViewController {

    var questions : [Question] = [Question(title: "Question 1", answers: ["jdcnjods","kmnoiwdsjfo", "mfuywehfiuw"],
                                           trueAnswer: 2)]
    
    private lazy var labelInfo: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.numberOfLines = 0
        label.text = "Example element 1"
        return label
    }()
    
    private lazy var tableView: UITableView = {
        let table = UITableView()
        table.translatesAutoresizingMaskIntoConstraints = false
        return table
    }()
    
    override func viewDidLoad() {
        super.viewDidLoad()
         print("did load")
        tableView.dataSource = self
        tableView.delegate = self
        tableView.register(UINib(nibName: "CellQuestion", bundle: nil), forCellReuseIdentifier: "CellQuestion")
        tableView.reloadSectionIndexTitles()
        
        view.addSubview(labelInfo)
        view.addSubview(tableView)
        
        NSLayoutConstraint.activate([
            
            labelInfo.topAnchor.constraint(equalTo: view.topAnchor, constant: 150),
            labelInfo.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            labelInfo.heightAnchor.constraint(equalToConstant: 50),
            labelInfo.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
            
            tableView.topAnchor.constraint(equalTo: labelInfo.bottomAnchor, constant: 20),
            tableView.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: -120),
            tableView.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 4),
            tableView.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -4),
            
        ])
    }
}

extension ElementController: UITableViewDelegate, UITableViewDataSource {
    func tableView(_: UITableView, numberOfRowsInSection _: Int) -> Int {
        return questions.count
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        guard let cell = tableView.dequeueReusableCell(withIdentifier: "CellQuestion") as? CellQuestion else {
            return UITableViewCell()
        }
        cell.setup(with: questions[indexPath.item])
        return cell
    }

    func numberOfSections(in _: UITableView) -> Int {
        return 1
    }

    func tableView(_: UITableView, heightForRowAt _: IndexPath) -> CGFloat {
        return UITableView.automaticDimension
    }
}

