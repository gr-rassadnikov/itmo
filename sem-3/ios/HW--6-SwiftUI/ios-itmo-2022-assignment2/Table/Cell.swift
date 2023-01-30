//
//  Cell.swift
//  ios-itmo-2022-assignment2
//
//  Created by Grigorii Rassadnikov on 26.10.2022.
//

import UIKit

class Cell: UITableViewCell {
    @IBOutlet var view: UIView!

    public var buttonArray = [UIButton]()
    public var stars = StarsView()
    public var page = Page(movieId: 1)

    private lazy var name: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.font = .systemFont(ofSize: 16)
        label.textColor = UIColor(named: "ColorCardTittle")
        label.numberOfLines = 0
        return label
    }()

    private lazy var author: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.font = .systemFont(ofSize: 16)
        label.textColor = UIColor(named: "ColorCardTittle")
        label.numberOfLines = 0
        return label
    }()

    private lazy var date: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.font = .systemFont(ofSize: 16)
        label.textColor = UIColor(named: "ColorCardTittle")
        label.numberOfLines = 0
        return label
    }()

    private lazy var starCanva: UIView = {
        let view = UIView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.backgroundColor = UIColor(named: "ColorBorde")
        return view
    }()

    public func setup(with page: Page) {
        author.text = page.author
        name.text = page.name
        date.text = page.date
        self.page = page

        view.layer.cornerRadius = 8
        view.layer.borderWidth = 1
        view.layer.borderColor = UIColor(named: "ColorBorde")?.cgColor

        if let backImage = page.image {
            view.backgroundColor = UIColor(patternImage: backImage).withAlphaComponent(0.35)
        }

        view.addSubview(name)
        view.addSubview(author)
        view.addSubview(starCanva)
        view.addSubview(date)

        for _ in 0 ..< 5 {
            buttonArray.append({
                let button = UIButton(type: .system)
                button.translatesAutoresizingMaskIntoConstraints = false
                button.setImage(UIImage(named: "StarGray.png"), for: .normal)
                button.tintColor = UIColor(named: "ColorStarsGray")
                return button
            }())
        }

        buttonArray[0].addTarget(self, action: #selector(editStar1), for: .touchUpInside)
        buttonArray[1].addTarget(self, action: #selector(editStar2), for: .touchUpInside)
        buttonArray[2].addTarget(self, action: #selector(editStar3), for: .touchUpInside)
        buttonArray[3].addTarget(self, action: #selector(editStar4), for: .touchUpInside)
        buttonArray[4].addTarget(self, action: #selector(editStar5), for: .touchUpInside)

        NSLayoutConstraint.activate([
            name.topAnchor.constraint(equalTo: view.topAnchor, constant: 10),
            name.bottomAnchor.constraint(equalTo: view.bottomAnchor, constant: -36),
            name.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 10),
            name.widthAnchor.constraint(equalToConstant: 170),

            author.topAnchor.constraint(equalTo: view.topAnchor, constant: 10),
            author.bottomAnchor.constraint(equalTo: view.bottomAnchor, constant: -36),
            author.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -10),
            author.leadingAnchor.constraint(equalTo: name.trailingAnchor, constant: 20),

            starCanva.bottomAnchor.constraint(equalTo: view.bottomAnchor, constant: -10),
            starCanva.leadingAnchor.constraint(equalTo: author.leadingAnchor),

            date.bottomAnchor.constraint(equalTo: view.bottomAnchor, constant: -10),
            date.leadingAnchor.constraint(equalTo: name.leadingAnchor, constant: 0),
        ])

        for ind in 0 ... 4 {
            addSubview(buttonArray[ind])
            NSLayoutConstraint.activate([
                buttonArray[ind].bottomAnchor.constraint(equalTo: starCanva.bottomAnchor),
                buttonArray[ind].leadingAnchor.constraint(equalTo: ind == 0 ? starCanva.leadingAnchor : buttonArray[ind - 1].trailingAnchor, constant: ind == 0 ? 0 : 12),
                buttonArray[ind].heightAnchor.constraint(equalToConstant: 20),
                buttonArray[ind].widthAnchor.constraint(equalToConstant: 20),
            ])
        }
        editStarsColor(number: page.cnt)
    }

    public func editStarsColor(number: Int) {
        page.cnt = number
        for ind in 0 ..< number {
            buttonArray[ind].tintColor = UIColor(named: "ColorStarsYellow")
        }
        for ind in number ..< 5 {
            buttonArray[ind].tintColor = UIColor(named: "ColorBorde")
        }
    }

    @objc
    private func editStar1() {
        editStarsColor(number: 1)
        editStarChangeServer(number: 1)
//        Storage.server.postMovieRequest(title: page.name, director: page.author, date: page.getYear(), raiting: page.cnt, posterId: page.imagePath, )
    }

    @objc
    private func editStar2() {
        editStarsColor(number: 2)
        editStarChangeServer(number: 2)
//        Storage.server.postMovieRequest(title: page.name, director: page.author, date: page.getYear(), raiting: page.cnt, posterId: page.imagePath)
    }

    @objc
    private func editStar3() {
        editStarsColor(number: 3)
        editStarChangeServer(number: 3)
//        Storage.server.postMovieRequest(title: page.name, director: page.author, date: page.getYear(), raiting: page.cnt, posterId: page.imagePath)
    }

    @objc
    private func editStar4() {
        editStarsColor(number: 4)
        editStarChangeServer(number: 4)
//        Storage.server.postMovieRequest(title: page.name, director: page.author, date: page.getYear(), raiting: page.cnt, posterId: page.imagePath)
    }

    @objc
    private func editStar5() {
        editStarsColor(number: 5)
        editStarChangeServer(number: 5)
//        Storage.server.postMovieRequest(title: page.name, director: page.author, date: page.getYear(), raiting: page.cnt, posterId: page.imagePath)
    }

    private func editStarChangeServer(number _: Int) {
        Storage.server.changeMovieRequest(movieId: page.movieId, title: page.name,
                                          director: page.author, date: page.getYear(), raiting: page.cnt,
                                          posterId: page.imagePath, comletiom: { movieId in
                                              self.page.movieId = movieId

                                          })
    }
}
