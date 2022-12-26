//
//  CardView.swift
//  ios-itmo-2022-assignment2
//
//  Created by Grigorii Rassadnikov on 13.10.2022.
//

import UIKit

class StarsView: UIView {
    public var isNotEmpty = false
    public var buttonArray = [UIButton]()
    public var score: Int = 0

    public lazy var labelComment: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.text = "Ваша оценка"
        label.font = UIFont(name: "Inter-Medium", size: 16)
        label.textColor = UIColor(named: "ColorStarsMessage")
        return label
    }()

    override init(frame: CGRect) {
        super.init(frame: frame)
        translatesAutoresizingMaskIntoConstraints = false

        for _ in 0 ..< 5 {
            buttonArray.append({
                let button = UIButton(type: .system)
                button.translatesAutoresizingMaskIntoConstraints = false
                button.setImage(UIImage(named: "StarGray.png"), for: .normal)
                button.tintColor = UIColor(named: "ColorStarsGray")
                return button
            }())
        }

        setupView()
    }

    @available(*, unavailable)
    required init?(coder _: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    private func setupView() {
        for ind in 0 ... 4 {
            addSubview(buttonArray[ind])
            NSLayoutConstraint.activate([
                buttonArray[ind].bottomAnchor.constraint(equalTo: bottomAnchor),
                buttonArray[ind].leadingAnchor.constraint(equalTo: ind == 0 ? leadingAnchor : buttonArray[ind - 1].trailingAnchor, constant: ind == 0 ? 0 : 16),
                buttonArray[ind].heightAnchor.constraint(equalToConstant: 38.4),
                buttonArray[ind].widthAnchor.constraint(equalToConstant: 38.4),
            ])
        }
        addSubview(labelComment)
        NSLayoutConstraint.activate([
            labelComment.topAnchor.constraint(equalTo: buttonArray[4].bottomAnchor, constant: 20),
            labelComment.centerXAnchor.constraint(equalTo: centerXAnchor),
        ])
    }

    public func editStarsColor(number: Int) {
        isNotEmpty = true
        score = number
        for ind in 0 ..< number {
            buttonArray[ind].tintColor = UIColor(named: "ColorStarsYellow")
        }
        for ind in number ..< 5 {
            buttonArray[ind].tintColor = UIColor(named: "ColorStarsGray")
        }
    }

    public func removeInput() {
        editStarsColor(number: 0)
        isNotEmpty = false
        labelComment.text = "Ваша оценка"
    }
}
