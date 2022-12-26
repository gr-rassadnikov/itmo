//
//  LogIn.swift
//  ios-itmo-2022-assignment3
//
//  Created by Grigorii Rassadnikov on 14.12.2022.
//

import UIKit

class RegisterController: UIViewController {
    var user: User?

    private lazy var labelTitlle: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.text = "Регистрация"
        label.font = UIFont(name: "HelveticaNeue-Bold", size: 30.0)
        label.textColor = .black
        return label
    }()

    private lazy var name = CardView(frame: view.frame, title: "Логин", placeholder: "Введите логин")
    private lazy var password = CardView(frame: view.frame, title: "Пароль", placeholder: "Введите пароль")
    private lazy var mail = CardView(frame: view.frame, title: "Электронная почта", placeholder: "Введите Электронная почта")

    private lazy var buttonRegister: UIButton = {
        let button = UIButton(type: .system)
        button.translatesAutoresizingMaskIntoConstraints = false
        button.layer.cornerRadius = 25
        button.setTitle("Регистрация", for: .normal)
        button.setTitleColor(.white, for: .normal)
        button.addTarget(self, action: #selector(didTapButtonRegister), for: .touchUpInside)
        button.backgroundColor = UIColor(named: "ColorSaveButtonStart")
        return button
    }()

    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = UIColor(named: "ColorBackground")
        view.addSubview(labelTitlle)
        view.addSubview(name)
        view.addSubview(password)
        view.addSubview(buttonRegister)
        view.addSubview(mail)

        name.inputTextField.addTarget(self, action: #selector(editName), for: .editingChanged)
        password.inputTextField.addTarget(self, action: #selector(editPassword), for: .editingChanged)
        mail.inputTextField.addTarget(self, action: #selector(editMail), for: .editingChanged)

        NSLayoutConstraint.activate([
            labelTitlle.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 40),
            labelTitlle.centerXAnchor.constraint(equalTo: view.centerXAnchor),

            name.topAnchor.constraint(equalTo: labelTitlle.bottomAnchor, constant: 16),
            name.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            name.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
            name.heightAnchor.constraint(equalToConstant: 73),

            name.topAnchor.constraint(equalTo: labelTitlle.bottomAnchor, constant: 16),
            name.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            name.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
            name.heightAnchor.constraint(equalToConstant: 73),

            password.topAnchor.constraint(equalTo: name.bottomAnchor, constant: 16),
            password.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            password.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
            password.heightAnchor.constraint(equalToConstant: 73),

            mail.topAnchor.constraint(equalTo: password.bottomAnchor, constant: 16),
            mail.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            mail.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
            mail.heightAnchor.constraint(equalToConstant: 73),

            buttonRegister.topAnchor.constraint(equalTo: mail.bottomAnchor, constant: 16),
            buttonRegister.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            buttonRegister.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
            buttonRegister.heightAnchor.constraint(equalToConstant: 51),

        ])
    }

    @objc
    private func didTapButtonRegister() {
        if name.isNotEmpty, password.isNotEmpty, mail.isNotEmpty, name.isValid, password.isValid, mail.isValid {
            if let log = name.inputTextField.text,
               let pas = password.inputTextField.text,
               let mai = mail.inputTextField.text
            {
                Storage.server.registerRequest(login: log, password: pas, mail: mai, comletion: { result in
                    Storage.user = User(login: result.username, password: pas, mail: result.email, token: result.token, id: result.id)
                    print("🤡 \(Storage.user!.token)")
                    guard let tableController = UIStoryboard(name: "Main", bundle: nil).instantiateInitialViewController() else {
                        return
                    }
                    self.navigationController?.pushViewController(tableController, animated: true)
                })
            } else {
                print("🆘 bad code, didTapButtonRegister, valid work bad, so valid fields are nil")
            }

        } else {
            print("--- ⚠️W : tap on Register button with not valid fields")
        }
    }

    @objc
    private func editName() {
        name.chahgeIsNotEmpty()
        name.checkIsValid(minSize: 1, maxSize: 16, onlyLetters: true)
        isAllNotEmpty()
    }

    @objc
    private func editPassword() {
        password.chahgeIsNotEmpty()
        password.checkIsValid(minSize: 1, maxSize: 16, onlyLetters: true)
        isAllNotEmpty()
    }

    @objc
    private func editMail() {
        mail.chahgeIsNotEmpty()
        mail.checkIsValid(minSize: 1, maxSize: 16, onlyLetters: true)
        isAllNotEmpty()
    }

    private func isAllNotEmpty() {
        if name.isNotEmpty, password.isNotEmpty, mail.isNotEmpty, name.isValid, password.isValid, mail.isValid {
            buttonRegister.backgroundColor = UIColor(named: "ColorSaveButtonEnd")
        } else {
            buttonRegister.backgroundColor = UIColor(named: "ColorSaveButtonStart")
        }
    }
}
