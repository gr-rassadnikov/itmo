//
//  ViewController.swift
//  ios-itmo-2022-assignment2
//
//  Created by Grigorii Rassadnikov on 26.10.2022.
//

import UIKit

class ViewController: UIViewController {
    @IBOutlet private var tableView: UITableView!

    var pages: [[Page]] = [
        [Page(author: "Джеймс Кэмерон", name: "Титаник", date: "03.11.1997", cnt: 5)],
        [Page(author: "Джеймс Кэмерон", name: "Аватар", date: "21.01.2009", cnt: 2)],
        [Page(author: "Дж. Дж. Абрамс", name: "Звёздные войны: Пробуждение силы", date: "04.04.2015", cnt: 4),
         Page(author: "Колин Треворроу", name: "Мир юрского периода", date: "23.03.2015", cnt: 1)],
        [Page(author: "Братья Руссо", name: "Мстители: Война бесконечности", date: "22.12.2018", cnt: 2)],
        [Page(author: "Джон Фавро", name: "Король Лев", date: "04.02.2019", cnt: 4),
         Page(author: "Братья Руссо", name: "Мстители: Финал", date: "01.11.2019", cnt: 1)],
        [Page(author: "Джон Уоттс", name: "Человек-паук: Нет пути домой", date: "12.06.2021", cnt: 1)],
        [Page(author:
            "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk",
            name: "IOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOSIOS",
            date: "01.01.2022", cnt: 5)],
    ]

    override func viewDidLoad() {
        super.viewDidLoad()
        tableView.dataSource = self
        tableView.delegate = self
        tableView.register(UINib(nibName: "Cell", bundle: nil), forCellReuseIdentifier: "Cell")
        tableView.sectionIndexColor = UIColor(named: "ColorCardTittle")
        tableView.reloadSectionIndexTitles()
    }

    @IBAction private func didTapButtonAdd(_: UIButton) {
        guard let pageViewCotroller: PageViewController = UIStoryboard(name: "PageViewController", bundle: nil).instantiateInitialViewController() else { return }
        pageViewCotroller.setParentController(parent: self)
        navigationController?.pushViewController(pageViewCotroller, animated: true)
    }

    func addPage(page: Page) {
        var indexPage = -1
        var lowerPage = -1
        for ind in 0 ..< pages.count {
            if pages[ind][0] < page {
                lowerPage = ind
            }
            if !(pages[ind][0] < page), !(page < pages[ind][0]) {
                indexPage = ind
                break
            }
        }

        tableView.beginUpdates()
        if indexPage == -1 {
            pages.insert([page], at: lowerPage + 1)
            tableView.insertSections([lowerPage + 1], with: .automatic)
        } else {
            tableView.insertRows(at: [IndexPath(row: pages[indexPage].count - 1, section: indexPage)], with: .automatic)
            pages[indexPage].insert(page, at: pages[indexPage].count)
        }
        tableView.endUpdates()
    }
}

extension ViewController: UITableViewDelegate, UITableViewDataSource {
    func tableView(_: UITableView, numberOfRowsInSection section: Int) -> Int {
        pages[section].count
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        guard let cell = tableView.dequeueReusableCell(withIdentifier: "Cell") as? Cell else {
            return UITableViewCell()
        }
        cell.setup(with: pages[indexPath.section][indexPath.item])
        return cell
    }

    func tableView(_: UITableView, titleForHeaderInSection section: Int) -> String? {
        if pages[section].count == 0 {
            return nil
        }
        return pages[section][0].date.components(separatedBy: ["."])[2]
    }

    func numberOfSections(in _: UITableView) -> Int {
        return pages.count
    }

    func tableView(_: UITableView, heightForRowAt _: IndexPath) -> CGFloat {
        return UITableView.automaticDimension
    }

    func tableView(_: UITableView, trailingSwipeActionsConfigurationForRowAt indexPath: IndexPath) -> UISwipeActionsConfiguration? {
        let actionDelete = UIContextualAction(style: .destructive, title: "Удалить") {
            _, _, _ in
            self.pages[indexPath.section].remove(at: indexPath.row)
            self.tableView.beginUpdates()
            self.tableView.deleteRows(at: [indexPath], with: .automatic)
            if self.pages[indexPath.section].isEmpty {
                self.pages.remove(at: indexPath.section)
                self.tableView.deleteSections([indexPath.section], with: .automatic)
            }
            self.tableView.endUpdates()
        }
        let alertController = UIAlertController(title: "Изменить поля", message: "Введите название фильма и режисссера", preferredStyle: .alert)

        alertController.addTextField()
        alertController.addTextField()

        let action1 = UIAlertAction(title: "Сохранить", style: .default) { _ in
            self.tableView.beginUpdates()
            guard let newName = alertController.textFields?[0].text else { return }
            if !newName.isEmpty {
                self.pages[indexPath.section][indexPath.row].name = newName
            }
            guard let newAuthor = alertController.textFields?[1].text else { return }
            if !newAuthor.isEmpty {
                self.pages[indexPath.section][indexPath.row].author = newAuthor
            }
            self.tableView.reloadRows(at: [indexPath], with: .automatic)
            self.tableView.endUpdates()
        }

        let action2 = UIAlertAction(title: "Назад", style: .destructive)
        alertController.addAction(action1)
        alertController.addAction(action2)

        let actionEdit = UIContextualAction(style: .normal, title: "Изменить") {
            _, _, _ in
            self.present(alertController, animated: true)
        }
//        actionDelete.image = UIImage(named: "Busket")
//        actionDelete.backgroundColor = UIColor(named: "ColorBackground")
        return UISwipeActionsConfiguration(actions: [actionDelete, actionEdit])
    }

//    func sectionIndexTitles(for tableView: UITableView) -> [String]? {
//        var sectionIndex: [String] = []
//        for startPage in pages {
//            sectionIndex.append(startPage[0].date.components(separatedBy: ["."])[2])
//        }
//        return sectionIndex
//    }
}
