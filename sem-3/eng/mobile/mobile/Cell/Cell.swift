//
//  Cell.swift
//  ios-itmo-2022-assignment2
//
//  Created by Grigorii Rassadnikov on 26.10.2022.
//

import UIKit

class Cell: UITableViewCell {
    @IBOutlet var view: UIView!

    private lazy var titleLabel: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.font = .systemFont(ofSize: 16)
        label.textColor = UIColor(named: "textLight")
        label.numberOfLines = 0
        return label
    }()

    private lazy var add: UIButton = {
        let button = UIButton()
        button.translatesAutoresizingMaskIntoConstraints = false
        button.setImage(UIImage(named: "add"), for: .normal)
        button.addTarget(self, action: #selector(didTapButtonAdd), for: .touchUpInside)
        return button
    }()

    private lazy var activity: Activity = .init(name: "")
    private var completion: ((Int) -> Void)?
    private var changeList: ((IndexPath) -> Void)?
    private var index: IndexPath = .init()

    public func setup(with activity: Activity, completion: @escaping (Int) -> Void, changeList: @escaping (IndexPath) -> Void, index: IndexPath) {
        view.layer.cornerRadius = 12
        self.activity = activity
        self.index = index
        self.changeList = changeList
        self.completion = completion
        titleLabel.text = activity.name

        if !activity.isChoosen {
            view.backgroundColor = UIColor(named: "grayCell")
            add.setImage(UIImage(named: "add"), for: .normal)
        } else {
            view.backgroundColor = UIColor(named: "orangeCell")
            add.setImage(UIImage(named: "choose"), for: .normal)
        }

        view.addSubview(titleLabel)
        view.addSubview(add)

        NSLayoutConstraint.activate([
            titleLabel.topAnchor.constraint(equalTo: view.topAnchor, constant: 16),
            titleLabel.bottomAnchor.constraint(equalTo: view.bottomAnchor, constant: -16),
            titleLabel.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            titleLabel.trailingAnchor.constraint(equalTo: add.leadingAnchor, constant: -32),

            add.centerYAnchor.constraint(equalTo: view.centerYAnchor),
            add.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -10),
            add.widthAnchor.constraint(equalToConstant: 32),
        ])
    }

    @objc
    private func didTapButtonAdd() {
        if activity.isChoosen {
            view.backgroundColor = UIColor(named: "grayCell")
            add.setImage(UIImage(named: "add"), for: .normal)
            guard let completion = completion else { return }
            completion(-1)
            guard let changeList = changeList else { return }
            changeList(index)
        } else {
            view.backgroundColor = UIColor(named: "orangeCell")
            add.setImage(UIImage(named: "choose"), for: .normal)
            guard let completion = completion else { return }
            completion(1)
            guard let changeList = changeList else { return }
            changeList(index)
        }
        activity.isChoosen = !activity.isChoosen
    }

    public func getIsChoosen() -> Bool {
        return activity.isChoosen
    }
}
