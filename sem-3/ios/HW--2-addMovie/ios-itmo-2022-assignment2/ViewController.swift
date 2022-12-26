//
//  ViewController.swift
//  ios-itmo-2022-assignment2
//
//  Created by rv.aleksandrov on 29.09.2022.
//

import UIKit

class ViewController: UIViewController {
//    private lazy var buttonSave: UIButton = {
//        let button = UIButton(type: .system)
//        button.translatesAutoresizingMaskIntoConstraints = false
//        button.layer.cornerRadius = 25
//        button.setTitle("Сохранить", for: .normal)
//        button.setTitleColor(.white, for: .normal)
//        button.addTarget(self, action: #selector(didTapButtonSave), for: .touchUpInside)
//        button.backgroundColor = UIColor(named: "ColorSaveButtonStart")
//        return button
//    }()
//
    private lazy var buttonSettings: UIButton = {
        let button = UIButton(type: .system)
        button.translatesAutoresizingMaskIntoConstraints = false
        button.layer.cornerRadius = 50
        button.setTitle("...", for: .normal)
        button.titleLabel?.font = UIFont(name: "HelveticaNeue-Bold", size: 25)
        button.setTitleColor(.black, for: .normal)
        button.layer.cornerRadius = 2
        button.layer.borderColor = UIColor(named: "ColorCardTittle")?.cgColor
        return button
    }()
    
    private lazy var buttonExplore: UIButton = {
        let button = UIButton(type: .system)
        button.translatesAutoresizingMaskIntoConstraints = false
        button.setTitle("Explore works", for: .normal)
        button.titleLabel?.font = UIFont(name: "HelveticaNeue-Bold", size: 12)
        button.backgroundColor = .black
        button.setTitleColor(.white, for: .normal)
        return button
    }()

    private lazy var labelTitlle: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.text = "Inbox"
        label.font = UIFont(name: "HelveticaNeue-Bold", size: 25.0)
        label.textColor = .black
        return label
    }()
    
    private lazy var labelText1: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.text = "Keep track of your conversations with galleries"
        label.font = UIFont(name: "HelveticaNeue-Bold", size: 18.0)
        label.textColor = .black
        return label
    }()
    private lazy var labelText2: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.text = "Contract galleries to learn more about works you want to collect. Use your inbox to stay on top of your archive"
        label.font = UIFont(name: "HelveticaNeue-Bold", size: 12.0)
        label.textColor = .black
        return label
    }()
    
//    private lazy var image = UIImage(named: "Image")

//    private lazy var cardView1 = CardView(frame: view.frame, title: "Название", placeholder: "Название фильма")
//    private lazy var cardView2 = CardView(frame: view.frame, title: "Режиссёр", placeholder: "Режиссёр фильма")
//    private lazy var cardView3 = CardView(frame: view.frame, title: "Год", placeholder: "Год выпуска", useDatePicker: true)
//
//    private lazy var starsView = StarsView(frame: view.frame)

    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = UIColor(named: "ColorBackground")

        view.addSubview(labelTitlle)
//        view.addSubview(cardView1)
//        view.addSubview(cardView2)
//        view.addSubview(cardView3)
//        view.addSubview(starsView)
        view.addSubview(buttonSettings)
        view.addSubview(buttonExplore)
        view.addSubview(labelText1)
        view.addSubview(labelText2)
//        image.translatesAutoresizingMaskIntoConstraints = false
//        view.addSubview(image)
//        view.addSubview(buttonSave)

//        cardView1.inputTextField.addTarget(self, action: #selector(editCardView1), for: .editingChanged)
//        cardView2.inputTextField.addTarget(self, action: #selector(editCardView2), for: .editingChanged)
//        cardView3.inputTextField.addTarget(self, action: #selector(editCardView3), for: .editingChanged)
//        starsView.buttonArray[0].addTarget(self, action: #selector(editStar1), for: .touchUpInside)
//        starsView.buttonArray[1].addTarget(self, action: #selector(editStar2), for: .touchUpInside)
//        starsView.buttonArray[2].addTarget(self, action: #selector(editStar3), for: .touchUpInside)
//        starsView.buttonArray[3].addTarget(self, action: #selector(editStar4), for: .touchUpInside)
//        starsView.buttonArray[4].addTarget(self, action: #selector(editStar5), for: .touchUpInside)

        NSLayoutConstraint.activate([
            labelTitlle.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 24),
            labelTitlle.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 32),
            
            buttonSettings.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 22),
            buttonSettings.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -24),
            
            buttonExplore.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 490),
            buttonExplore.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 24),
            buttonExplore.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -24),
            buttonExplore.heightAnchor.constraint(equalToConstant: 54),
            
            labelText1.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 300),
            labelText1.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 24),
            labelText1.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -24),
            labelText1.heightAnchor.constraint(equalToConstant: 54),
            
            labelText2.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 390),
            labelText2.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 24),
            labelText2.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -24),
            labelText2.heightAnchor.constraint(equalToConstant: 54)
            
            
            
        

//            cardView1.topAnchor.constraint(equalTo: labelTitlle.bottomAnchor, constant: 40),
//            cardView1.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
//            cardView1.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
//            cardView1.heightAnchor.constraint(equalToConstant: 73),
//
//            cardView2.topAnchor.constraint(equalTo: cardView1.bottomAnchor, constant: 16),
//            cardView2.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
//            cardView2.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
//            cardView2.heightAnchor.constraint(equalToConstant: 73),
//
//            cardView3.topAnchor.constraint(equalTo: cardView2.bottomAnchor, constant: 16),
//            cardView3.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
//            cardView3.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
//            cardView3.heightAnchor.constraint(equalToConstant: 73),
//
//            buttonSave.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
//            buttonSave.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
//            buttonSave.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: -33),
//            buttonSave.heightAnchor.constraint(equalToConstant: 51),
//
//            starsView.topAnchor.constraint(equalTo: cardView3.bottomAnchor, constant: 48),
//            starsView.centerXAnchor.constraint(equalTo: view.centerXAnchor),
//            starsView.widthAnchor.constraint(equalToConstant: 256),
//            starsView.heightAnchor.constraint(equalToConstant: 35.4),
//
//            buttonRemove.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
//            buttonRemove.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
//            buttonRemove.bottomAnchor.constraint(equalTo: buttonSave.topAnchor, constant: -33),
//            buttonRemove.heightAnchor.constraint(equalToConstant: 51),
        ])
    }

}
