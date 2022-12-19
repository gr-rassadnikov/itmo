//
//  CellCollection.swift
//  mobile
//
//  Created by Grigorii Rassadnikov on 18.12.2022.
//

import Foundation
import UIKit

class CellCollection: UICollectionView {
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
        button.setTitle("+", for: .normal)
        button.titleLabel?.font = .systemFont(ofSize: 32)
        button.setTitleColor(UIColor(named: "textLight"), for: .normal)

        return button
    }()

    public func setup(with title: String) {
        view.layer.cornerRadius = 12
        titleLabel.text = title
        view.backgroundColor = UIColor(named: "orangeCell")

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
}
