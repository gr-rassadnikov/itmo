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
        for i in 0 ... 4 {
            addSubview(buttonArray[i])
            NSLayoutConstraint.activate([
                buttonArray[i].bottomAnchor.constraint(equalTo: bottomAnchor),
                buttonArray[i].leadingAnchor.constraint(equalTo: i == 0 ? leadingAnchor : buttonArray[i - 1].trailingAnchor, constant: i == 0 ? 0 : 16),
                buttonArray[i].heightAnchor.constraint(equalToConstant: 38.4),
                buttonArray[i].widthAnchor.constraint(equalToConstant: 38.4),
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
        for i in 0 ..< number {
            buttonArray[i].tintColor = UIColor(named: "ColorStarsYellow")
        }
        for i in number ..< 5 {
            buttonArray[i].tintColor = UIColor(named: "ColorStarsGray")
        }
    }

    public func removeInput() {
        editStarsColor(number: 0)
        isNotEmpty = false
        labelComment.text = "Ваша оценка"
    }
}
