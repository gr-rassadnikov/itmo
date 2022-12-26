//
//  ViewController.swift
//  ios-itmo-2022-assignment2
//
//  Created by rv.aleksandrov on 29.09.2022.
//

import Foundation
import UIKit

class PageViewController: UIViewController {
    private var parentController = ViewController()

    public func setParentController(parent: ViewController) {
        parentController = parent
    }

    private lazy var buttonSave: UIButton = {
        let button = UIButton(type: .system)
        button.translatesAutoresizingMaskIntoConstraints = false
        button.layer.cornerRadius = 25
        button.setTitle("Сохранить", for: .normal)
        button.setTitleColor(.white, for: .normal)
        button.addTarget(self, action: #selector(didTapButtonSave), for: .touchUpInside)
        button.backgroundColor = UIColor(named: "ColorSaveButtonStart")
        return button
    }()

    private lazy var buttonRemove: UIButton = {
        let button = UIButton(type: .system)
        button.translatesAutoresizingMaskIntoConstraints = false
        button.layer.cornerRadius = 25
        button.setTitle("Очистить", for: .normal)
        button.setTitleColor(.white, for: .normal)
        button.addTarget(self, action: #selector(didTapButtonRemove), for: .touchUpInside)
        button.backgroundColor = .blue
        return button
    }()

    private lazy var labelTitlle: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.text = "Фильм"
        label.font = UIFont(name: "HelveticaNeue-Bold", size: 30.0)
        label.textColor = .black
        return label
    }()

    lazy var cardView1 = CardView(frame: view.frame, title: "Название", placeholder: "Название фильма")
    lazy var cardView2 = CardView(frame: view.frame, title: "Режиссёр", placeholder: "Режиссёр фильма")
    lazy var cardView3 = CardView(frame: view.frame, title: "Год", placeholder: "Год выпуска", useDatePicker: true)

    lazy var starsView = StarsView(frame: view.frame)

    lazy var poster: UIButton = {
        let view = UIButton()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.backgroundColor = UIColor(named: "ColorSaveButtonStart")
        view.setTitle("Добавить постер", for: .normal)
        view.setTitleColor(.black, for: .normal)
        view.addTarget(self, action: #selector(didTapPoster), for: .touchUpInside)
        return view
    }()

    var imagePicker: UIImagePickerController {
        let vc = UIImagePickerController()
        vc.sourceType = .photoLibrary
        vc.delegate = self
        vc.allowsEditing = true
        return vc
    }

    var image: UIImage?

    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = UIColor(named: "ColorBackground")

        view.addSubview(labelTitlle)
        view.addSubview(poster)
        view.addSubview(cardView1)
        view.addSubview(cardView2)
        view.addSubview(cardView3)
        view.addSubview(starsView)
        view.addSubview(buttonRemove)
        view.addSubview(buttonSave)

        cardView1.inputTextField.addTarget(self, action: #selector(editCardView1), for: .editingChanged)
        cardView2.inputTextField.addTarget(self, action: #selector(editCardView2), for: .editingChanged)
        cardView3.inputTextField.addTarget(self, action: #selector(editCardView3), for: .editingChanged)
        starsView.buttonArray[0].addTarget(self, action: #selector(editStar1), for: .touchUpInside)
        starsView.buttonArray[1].addTarget(self, action: #selector(editStar2), for: .touchUpInside)
        starsView.buttonArray[2].addTarget(self, action: #selector(editStar3), for: .touchUpInside)
        starsView.buttonArray[3].addTarget(self, action: #selector(editStar4), for: .touchUpInside)
        starsView.buttonArray[4].addTarget(self, action: #selector(editStar5), for: .touchUpInside)

        NSLayoutConstraint.activate([
            labelTitlle.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            labelTitlle.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 16),

            cardView1.topAnchor.constraint(equalTo: poster.bottomAnchor, constant: 16),
            cardView1.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            cardView1.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
            cardView1.heightAnchor.constraint(equalToConstant: 73),

            cardView2.topAnchor.constraint(equalTo: cardView1.bottomAnchor, constant: 16),
            cardView2.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            cardView2.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
            cardView2.heightAnchor.constraint(equalToConstant: 73),

            cardView3.topAnchor.constraint(equalTo: cardView2.bottomAnchor, constant: 16),
            cardView3.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            cardView3.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
            cardView3.heightAnchor.constraint(equalToConstant: 73),

            buttonSave.leadingAnchor.constraint(equalTo: view.centerXAnchor, constant: 8),
            buttonSave.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
            buttonSave.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: -33),
            buttonSave.heightAnchor.constraint(equalToConstant: 51),

            starsView.topAnchor.constraint(equalTo: cardView3.bottomAnchor, constant: 28),
            starsView.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            starsView.widthAnchor.constraint(equalToConstant: 256),
            starsView.heightAnchor.constraint(equalToConstant: 35.4),

            buttonRemove.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            buttonRemove.trailingAnchor.constraint(equalTo: view.centerXAnchor, constant: -8),
            buttonRemove.bottomAnchor.constraint(equalTo: buttonSave.bottomAnchor, constant: 0),
            buttonRemove.heightAnchor.constraint(equalToConstant: 51),

            poster.topAnchor.constraint(equalTo: labelTitlle.bottomAnchor, constant: 20),
            poster.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            poster.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
            poster.heightAnchor.constraint(equalToConstant: 171),
        ])
    }

    @objc
    private func didTapButtonSave() {
        if cardView1.isNotEmpty, cardView2.isNotEmpty, cardView3.isNotEmpty, starsView.isNotEmpty, cardView1.isValid, cardView2.isValid, cardView3.isValid {
            if let imageForSave = image {
                // ?????               let urlToImage = saveImage(imageName: poster_id, image: imageForSave)
                Storage.server.postImageRequest(image: imageForSave, completion: { [self] posterId in
                    Storage.server.postMovieRequest(title: cardView1.inputTextField.text!,
                                                    director: cardView2.inputTextField.text!, date: toYear(date: cardView3.inputTextField.text!), raiting: starsView.score, posterId: posterId, comletiom: { [self] movieId in
                                                        parentController.addPage(page: Page(author: cardView2.inputTextField.text!,
                                                                                            name: cardView1.inputTextField.text!,
                                                                                            date: String(toYear(date: cardView3.inputTextField.text!)),
                                                                                            cnt: starsView.score,
                                                                                            image: image, movieId: movieId))
                                                    })
                })

            } else {
                print("--- ⚠️W: don't find image from poster.image")
                return
            }
            navigationController?.popViewController(animated: true)
        }
    }

    @objc
    private func didTapButtonRemove() {
        cardView1.removeInput()
        cardView2.removeInput()
        cardView3.removeInput()
        starsView.removeInput()
        isAllNotEmpty()
    }

    @objc
    private func didTapPoster() {
        present(imagePicker, animated: true)
    }

    @objc
    private func editCardView1() {
        cardView1.chahgeIsNotEmpty()
        cardView1.checkIsValid(minSize: 1, maxSize: 300, onlyLetters: false)
        isAllNotEmpty()
    }

    @objc
    private func editCardView2() {
        cardView2.chahgeIsNotEmpty()
        cardView2.checkIsValid(minSize: 3, maxSize: 300, onlyLetters: true)
        isAllNotEmpty()
    }

    @objc
    private func editCardView3() {
        cardView3.chahgeIsNotEmpty()
        cardView3.checkIsValid(minSize: -1, maxSize: -1, onlyLetters: false)
        isAllNotEmpty()
    }

    @objc
    private func editStar1() {
        starsView.editStarsColor(number: 1)
        starsView.labelComment.text = "Ужасно"
        isAllNotEmpty()
    }

    @objc
    private func editStar2() {
        starsView.editStarsColor(number: 2)
        starsView.labelComment.text = "Плохо"
        isAllNotEmpty()
    }

    @objc
    private func editStar3() {
        starsView.editStarsColor(number: 3)
        starsView.labelComment.text = "Нормально"
        isAllNotEmpty()
    }

    @objc
    private func editStar4() {
        starsView.editStarsColor(number: 4)
        starsView.labelComment.text = "Хорошо"
        isAllNotEmpty()
    }

    @objc
    private func editStar5() {
        starsView.editStarsColor(number: 5)
        starsView.labelComment.text = "AMAZING!"
        isAllNotEmpty()
    }

    private func isAllNotEmpty() {
        if cardView1.isNotEmpty, cardView2.isNotEmpty, cardView3.isNotEmpty, starsView.isNotEmpty, cardView1.isValid, cardView2.isValid, cardView3.isValid {
            buttonSave.backgroundColor = UIColor(named: "ColorSaveButtonEnd")
        } else {
            buttonSave.backgroundColor = UIColor(named: "ColorSaveButtonStart")
        }
    }
}

extension PageViewController: UIImagePickerControllerDelegate, UINavigationControllerDelegate {
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey: Any]) {
        if let image = info[UIImagePickerController.InfoKey(rawValue: "UIImagePickerControllerEditedImage")] as? UIImage {
            self.image = image
            poster.setImage(self.image, for: .normal)
        }
        picker.dismiss(animated: true)
    }

    func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        picker.dismiss(animated: true)
    }
}
