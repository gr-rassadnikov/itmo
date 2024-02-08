//
//  ViewController.swift
//  testYInter
//
//  Created by Grigorii Rassadnikov on 26.03.2023.
//

import UIKit
// final class A {
//    private let view = UIView()
//
//    deinit {
//        view.removeFromSuperview()
//    }
// }
//
// final class B {
//    private let backgroundQueue = DispatchQueue(label: "some queue")
//
//    func doSmth(completion: @escaping () -> Void) {
//        backgroundQueue.async {
//            for i in 1...10000000{
//                let r = i
//            }
//            DispatchQueue.main.async {
//                completion()
//            }
//        }
//    }
// }
//
// final class C {
//    private let b = B()
//    private var a: A? = A()
//
//    func doTheJob() {
//        b.doSmth { [a] in
//            print(String(describing: a!))
//        }
//        a = nil
//    }
// }

final class BankAccount {
    let id: String
    var amount: Int
    var isFrozen: Bool
}

extension BankAccount: Hashable {
    static func == (lhs: BankAccount, rhs: BankAccount) -> Bool {
        return lhs.id == rhs.id
    }

    public func hash(into hasher: inout Hasher) {
        return hasher.combine(id)
    }
}

class ViewController: UIViewController {
    override func viewDidLoad() {
        let s = Set<BankAccount>()
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        let canvas = view!
//        let v1 = UIView(frame: .zero)
//        v1.frame = CGRect(x: 10, y: 10, width: 300, height: 300)
//        v1.backgroundColor = .blue
//        canvas.addSubview(v1)
//
//        let v2 = UIView(frame: .zero)
//        v2.frame = CGRect(x: 100, y: 10, width: 150, height: 150)
//        v2.backgroundColor = .red
//        v1.addSubview(v2)
//
//        let v3 = UIView(frame: .zero)
//        v3.frame = CGRect(x: 10, y: 100, width: 150, height: 150)
//        v3.backgroundColor = .green
//        v1.addSubview(v3)
//
//        let v4 = UIView(frame: .zero)
//        v4.frame = CGRect(x: 10, y: 10, width: 20, height: 20)
//        v4.backgroundColor = .yellow
//        v4.transform = CGAffineTransform(translationX: 140, y: 80)
//        v1.addSubview(v4)

//        v1,v1,v2,v1,v3,translationX:140,y:80,v1,v4
//        v1,v1,v2,v1,v3,translationX:140,y:80,v1,v4

//        print("start")
//        let a = A()
//        view.addSubview()
//        let c = C()
//        c.doTheJob()
//        print("end")

        let v1 = UIView(frame: .zero)
        v1.frame = CGRect(x: 10, y: 10, width: 300, height: 300)
        v1.backgroundColor = .blue
        canvas.addSubview(v1)

        let v2 = UIView(frame: .zero)
        v2.frame = CGRect(x: 100, y: 10, width: 150, height: 150)
        v2.backgroundColor = .red
        v1.addSubview(v2)

        let v3 = UIView(frame: .zero)
        v3.frame = CGRect(x: 10, y: 100, width: 150, height: 150)
        v3.backgroundColor = .green
        v1.addSubview(v3)

        let v4 = UIView(frame: .zero)
        v4.frame = CGRect(x: 10, y: 10, width: 20, height: 20)
        v4.backgroundColor = .yellow
        v4.transform = CGAffineTransform(translationX: 140, y: 80)
        v1.addSubview(v4)
    }
}
