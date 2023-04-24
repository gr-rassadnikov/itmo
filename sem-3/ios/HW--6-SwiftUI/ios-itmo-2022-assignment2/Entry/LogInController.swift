//
//  LogIn.swift
//  ios-itmo-2022-assignment3
//
//  Created by Grigorii Rassadnikov on 14.12.2022.
//

import Foundation
import UIKit

class LogInController: UIViewController {
    private lazy var labelTitlle: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.text = "Войти"
        label.font = UIFont(name: "HelveticaNeue-Bold", size: 30.0)
        label.textColor = .black
        return label
    }()

    private lazy var name = CardView(frame: view.frame, title: "Логин", placeholder: "Введите логин")
    private lazy var password = CardView(frame: view.frame, title: "Пароль", placeholder: "Введите пароль")

    private lazy var buttonEnter: UIButton = {
        let button = UIButton(type: .system)
        button.translatesAutoresizingMaskIntoConstraints = false
        button.layer.cornerRadius = 25
        button.setTitle("Войти", for: .normal)
        button.setTitleColor(.white, for: .normal)
        button.addTarget(self, action: #selector(didTapButtonEnter), for: .touchUpInside)
        button.backgroundColor = UIColor(named: "ColorSaveButtonStart")
        return button
    }()

    private lazy var buttonRegister: UIButton = {
        let button = UIButton(type: .system)
        button.translatesAutoresizingMaskIntoConstraints = false
        button.setTitle("Регистрация", for: .normal)
        button.setTitleColor(UIColor(named: "ColorSaveButtonEnd"), for: .normal)
        button.addTarget(self, action: #selector(didTapButtonRegister), for: .touchUpInside)
        return button
    }()

    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = UIColor(named: "ColorBackground")
        view.addSubview(labelTitlle)
        view.addSubview(name)
        view.addSubview(password)
        view.addSubview(buttonEnter)
        view.addSubview(buttonRegister)

        if let user = Storage.user {
            name.inputTextField.text = user.login
            password.inputTextField.text = user.password
            editName()
            editPassword()
            isAllNotEmpty()
        }

        name.inputTextField.addTarget(self, action: #selector(editName), for: .editingChanged)
        password.inputTextField.addTarget(self, action: #selector(editPassword), for: .editingChanged)

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

            buttonEnter.topAnchor.constraint(equalTo: password.bottomAnchor, constant: 16),
            buttonEnter.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            buttonEnter.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
            buttonEnter.heightAnchor.constraint(equalToConstant: 51),

            buttonRegister.topAnchor.constraint(equalTo: buttonEnter.bottomAnchor, constant: 18),
            buttonRegister.centerXAnchor.constraint(equalTo: view.centerXAnchor),

        ])
    }

    @objc
    private dynamic func didTapButtonEnter() {
        if name.isNotEmpty, password.isNotEmpty, name.isValid, password.isValid {
            if let log = name.inputTextField.text,
               let pas = password.inputTextField.text
            {
                Storage.server.loginRequest(login: log, password: pas, mail: Storage.user!.mail, comletion: { result in
                    Storage.user = User(login: result.username, password: pas, mail: result.email, token: result.token, id: result.id)
                    print("🤡 \(Storage.user!.token)")
                    guard let tableController = UIStoryboard(name: "Main", bundle: nil).instantiateInitialViewController() else {
                        return
                    }
                    self.navigationController?.pushViewController(tableController, animated: true)
                })
            } else {
                print("🆘 bad code, didTapButtonEnter, valid work bad, so valid fields are nil")
            }
        } else {
            print("--- ⚠️W : tap on Enter button with not valid fields")
        }
    }

    @objc
    private func didTapButtonRegister() {
        guard let pageRegisterController = UIStoryboard(name: "Register", bundle: nil).instantiateInitialViewController() else {
            return
        }
        navigationController?.pushViewController(pageRegisterController, animated: true)
    }

    @objc
    private func editName() {
        name.chahgeIsNotEmpty()
        name.checkIsValid(minSize: 1, maxSize: 16, onlyLetters: false)
        isAllNotEmpty()
    }

    @objc
    private func editPassword() {
        password.chahgeIsNotEmpty()
        password.checkIsValid(minSize: 1, maxSize: 16, onlyLetters: false)
        isAllNotEmpty()
    }

    private func isAllNotEmpty() {
        if name.isNotEmpty, password.isNotEmpty, name.isValid, password.isValid {
            buttonEnter.backgroundColor = UIColor(named: "ColorSaveButtonEnd")
        } else {
            buttonEnter.backgroundColor = UIColor(named: "ColorSaveButtonStart")
        }
    }
}
