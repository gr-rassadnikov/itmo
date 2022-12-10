//
//  CardView.swift
//  ios-itmo-2022-assignment2
//
//  Created by Grigorii Rassadnikov on 13.10.2022.
//

import UIKit

class CardView: UIView {
    public var isNotEmpty = false
    public var isValid = true
    public var useDatePicker = false

    private lazy var dateFormatter = DateFormatter()

    private lazy var title: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.font = .systemFont(ofSize: 12)
        label.textColor = UIColor(named: "ColorCardTittle")
        return label
    }()

    private lazy var cornerUIView: UIView = {
        let view = UIView()
        view.layer.backgroundColor = UIColor(named: "ColorTextField")?.cgColor
        view.layer.cornerRadius = 8
        view.layer.borderWidth = 1
        view.layer.borderColor = UIColor(named: "ColorBorde")?.cgColor
        view.translatesAutoresizingMaskIntoConstraints = false
        return view
    }()

    public lazy var inputTextField: UITextField = {
        let input = UITextField()
        input.translatesAutoresizingMaskIntoConstraints = false
        input.font = .systemFont(ofSize: 16)
        return input
    }()

    private lazy var datePicker = UIDatePicker(frame: self.frame)
    private lazy var toolBar = UIToolbar(frame: self.frame)

    init(frame: CGRect, title: String, placeholder: String, useDatePicker: Bool = false) {
        super.init(frame: frame)
        self.title.text = title
        self.useDatePicker = useDatePicker
        setupView(placeholder: placeholder)
        translatesAutoresizingMaskIntoConstraints = false
    }

    @available(*, unavailable)
    required init?(coder _: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    private func setupView(placeholder: String) {
        addSubview(title)
        addSubview(cornerUIView)
        cornerUIView.addSubview(inputTextField)

        NSLayoutConstraint.activate([
            title.topAnchor.constraint(equalTo: topAnchor),
            title.leadingAnchor.constraint(equalTo: leadingAnchor),
            title.trailingAnchor.constraint(equalTo: trailingAnchor),

            cornerUIView.leadingAnchor.constraint(equalTo: leadingAnchor),
            cornerUIView.trailingAnchor.constraint(equalTo: trailingAnchor),
            cornerUIView.bottomAnchor.constraint(equalTo: bottomAnchor),
            cornerUIView.heightAnchor.constraint(equalToConstant: 50),

            inputTextField.leadingAnchor.constraint(equalTo: leadingAnchor, constant: 16),
            inputTextField.trailingAnchor.constraint(equalTo: trailingAnchor),
            inputTextField.centerYAnchor.constraint(equalTo: cornerUIView.centerYAnchor),
            inputTextField.heightAnchor.constraint(equalToConstant: 19),
        ])

        inputTextField.placeholder = placeholder
        if useDatePicker {
            datePicker.translatesAutoresizingMaskIntoConstraints = false
            toolBar.translatesAutoresizingMaskIntoConstraints = false

            toolBar.sizeToFit()

            let doneButton = UIBarButtonItem(barButtonSystemItem: .done, target: self, action: #selector(didTapDoneButton))
            let closeButton = UIBarButtonItem(barButtonSystemItem: .close, target: self, action: #selector(didTapCloseButton))

            toolBar.setItems([doneButton, closeButton], animated: true)

            datePicker.preferredDatePickerStyle = .wheels
            datePicker.datePickerMode = .date

            inputTextField.inputView = datePicker
            inputTextField.inputAccessoryView = toolBar

            dateFormatter.timeStyle = .none
            dateFormatter.dateFormat = "dd.MM.yyy"
        }
    }

    @objc
    private func didTapDoneButton() {
        inputTextField.text = dateFormatter.string(from: datePicker.date)
        isValid = true
        isNotEmpty = true
        endEditing(true)
    }

    @objc
    private func didTapCloseButton() {
        endEditing(true)
    }

    public func chahgeIsNotEmpty() {
        isNotEmpty = true
        if inputTextField.text == "" {
            isNotEmpty = false
        }
    }

    public func removeInput() {
        isNotEmpty = false
        cornerUIView.layer.borderColor = UIColor(named: "ColorBorde")?.cgColor
        title.textColor = UIColor(named: "ColorCardTittle")
        inputTextField.text = ""
    }

    public func checkIsValid(minSize: Int, maxSize: Int, onlyLetters: Bool) {
        isValid = true
        if useDatePicker {
            guard let inputText = inputTextField.text else {
                isValid = false
                return
            }
            if dateFormatter.date(from: inputText) == nil {
                isValid = false
            }
        } else {
            guard let str = inputTextField.text else {
                isValid = false
                return
            }
            if str.count < minSize || maxSize < str.count {
                isValid = false
            }
            if onlyLetters, !str.isEmpty {
                if !str[str.startIndex].isUppercase {
                    isValid = false
                }
                for chr in str {
                    if !(chr >= "a" && chr <= "z"), !(chr >= "A" && chr <= "Z"), !(chr >= "А" && chr <= "Я"), !(chr >= "а" && chr <= "я"), chr != " " {
                        isValid = false
                        break
                    }
                }
            }
        }

        if !isValid {
            cornerUIView.layer.borderColor = UIColor(named: "ColorNotValid")?.cgColor
            title.textColor = UIColor(named: "ColorNotValid")
        } else {
            cornerUIView.layer.borderColor = UIColor(named: "ColorBorde")?.cgColor
            title.textColor = UIColor(named: "ColorCardTittle")
        }
    }
}
