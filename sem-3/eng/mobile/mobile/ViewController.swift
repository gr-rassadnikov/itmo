//
//  ViewController.swift
//  mobile
//
//  Created by Grigorii Rassadnikov on 18.12.2022.
//

import UIKit

class ViewController: UIViewController {
    private var cntChoosenActivities = 0

    private var activities: [Activity] =
        [
            Activity(name: "Юмор"),
            Activity(name: "Еда"),
            Activity(name: "Зимние виды спорта (хоккей, горные лыжи, беговые лыжи, фигурное катание)"),
            Activity(name: "Прогулки"),
            Activity(name: "Решать задачки по математике или писать код до 5 утра каждый день"),
            Activity(name: "Политика"),
            Activity(name: "Новости"),
            Activity(name: "Аквтиность сюрприз с очень длинным названием, для проверки изменения размера ячейки... и добавим еще много длинного ненужного текста для отображения"),
            Activity(name: "Кино"),
            Activity(name: "Рестораны"), Activity(name: "Автомобили"),
            Activity(name: "Сериалы"),
            Activity(name: "Рецепты"),
            Activity(name: "Работа"),
        ]

    private lazy var tableView: UITableView = {
        let table = UITableView()
        table.translatesAutoresizingMaskIntoConstraints = false
        table.backgroundColor = UIColor(named: "background")
        return table
    }()

    private lazy var labelInfo: UILabel = {
        let label = UILabel()
        label.translatesAutoresizingMaskIntoConstraints = false
        label.numberOfLines = 0
        label.textColor = UIColor(named: "textGray")
        label.text = "Отметьте то, что вам интересно, чтобы настроить Дзен"
        return label
    }()

    private lazy var buttonLate: UIButton = {
        let button = UIButton()
        button.translatesAutoresizingMaskIntoConstraints = false
        button.layer.cornerRadius = 24
        button.setTitle("Позже", for: .normal)
        button.setTitleColor(UIColor(named: "textLight"), for: .normal)
        button.titleLabel?.font = .systemFont(ofSize: 16)
        button.addTarget(self, action: #selector(didTapButtonLate), for: .touchUpInside)
        button.backgroundColor = UIColor(named: "grayCell")
        return button
    }()

    private lazy var buttonContinue: UIButton = {
        let button = UIButton()
        button.translatesAutoresizingMaskIntoConstraints = false
        button.layer.cornerRadius = 40
        button.setTitle("Продолжить", for: .normal)
        button.setTitleColor(UIColor(named: "textDark"), for: .normal)
        button.titleLabel?.font = .systemFont(ofSize: 16)
        button.addTarget(self, action: #selector(didTapButtonContinue), for: .touchUpInside)
        button.backgroundColor = UIColor(named: "bgWhiteBt")
        return button
    }()

    private var buttonContinueConstraints: [NSLayoutConstraint] = []

    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = UIColor(named: "background")
        tableView.dataSource = self
        tableView.delegate = self
        tableView.register(UINib(nibName: "Cell", bundle: nil), forCellReuseIdentifier: "Cell")
        tableView.reloadSectionIndexTitles()

        view.addSubview(labelInfo)
        view.addSubview(buttonLate)
        view.addSubview(tableView)

        NSLayoutConstraint.activate([
            labelInfo.topAnchor.constraint(equalTo: view.topAnchor, constant: 50),
            labelInfo.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 16),
            labelInfo.heightAnchor.constraint(equalToConstant: 50),
            labelInfo.trailingAnchor.constraint(equalTo: buttonLate.leadingAnchor, constant: -16),

            buttonLate.topAnchor.constraint(equalTo: labelInfo.topAnchor),
            buttonLate.bottomAnchor.constraint(equalTo: labelInfo.bottomAnchor),
            buttonLate.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -16),
            buttonLate.widthAnchor.constraint(equalToConstant: 80),

            tableView.topAnchor.constraint(equalTo: labelInfo.bottomAnchor, constant: 20),
            tableView.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: -120),
            tableView.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 4),
            tableView.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -4),
        ])

        buttonContinueConstraints = [buttonContinue.centerXAnchor.constraint(equalTo: view.centerXAnchor),
                                     buttonContinue.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: -20),
                                     buttonContinue.heightAnchor.constraint(equalToConstant: 80),
                                     buttonContinue.widthAnchor.constraint(equalToConstant: 210)]
    }

    private func cntCA(with: Int) {
        cntChoosenActivities += with
        if cntChoosenActivities > 0 {
            activateButtonContinue()
        } else {
            deactivateButtonContinue()
        }
    }

    private func changeList(with: IndexPath) {
        activities[with.item].isChoosen = !activities[with.item].isChoosen
    }

    private func activateButtonContinue() {
        view.addSubview(buttonContinue)
        NSLayoutConstraint.activate(buttonContinueConstraints)
    }

    private func deactivateButtonContinue() {
        buttonContinue.removeFromSuperview()
        NSLayoutConstraint.deactivate(buttonContinueConstraints)
    }

    @objc
    private func didTapButtonLate() {
        print("LOG : didTapButtonLate")
    }

    @objc
    private func didTapButtonContinue() {
        print("LOG : didTapButtonContinue")
    }
}

extension ViewController: UITableViewDelegate, UITableViewDataSource {
    func tableView(_: UITableView, numberOfRowsInSection _: Int) -> Int {
        activities.count
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        guard let cell = tableView.dequeueReusableCell(withIdentifier: "Cell") as? Cell else {
            return UITableViewCell()
        }
        cell.setup(with: activities[indexPath.item], completion: cntCA, changeList: changeList, index: indexPath)
        activities[indexPath.item].isChoosen = cell.getIsChoosen()
        return cell
    }

    func numberOfSections(in _: UITableView) -> Int {
        1
    }

    func tableView(_: UITableView, heightForRowAt _: IndexPath) -> CGFloat {
        return UITableView.automaticDimension
    }
}
