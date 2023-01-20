//
//  ViewController.swift
//  vkCupRound2
//
//  Created by Grigorii Rassadnikov on 15.01.2023.
//

import UIKit

class ViewController: UIViewController {

    
    private lazy var titleLabel : UILabel = {
        let title = UILabel()
        title.translatesAutoresizingMaskIntoConstraints = false
        title.text = "Obout my app"
        return title
    }()
    
    private lazy var el1Button : UIButton = {
        let button = UIButton(type: .system)
        button.translatesAutoresizingMaskIntoConstraints = false
        button.setTitle("element 1", for: .normal)
        button.addTarget(self, action: #selector(didTapButtonEllement1), for: .touchUpInside)
        return button
    }()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        view.addSubview(titleLabel)
        view.addSubview(el1Button)
        
        NSLayoutConstraint.activate([
            titleLabel.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            titleLabel.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 32),
            titleLabel.heightAnchor.constraint(equalToConstant: 100),
            
            el1Button.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            el1Button.topAnchor.constraint(equalTo: titleLabel.bottomAnchor),
            el1Button.heightAnchor.constraint(equalToConstant: 50),
            
        ])
        
        
    }
    
    @objc
    private func didTapButtonEllement1(){
        guard let element1Controller = UIStoryboard(name: "Element", bundle: nil).instantiateInitialViewController() as? ElementController else {
            print("else")
            return
        }
        print("push")
        self.navigationController?.pushViewController(element1Controller, animated: true)
        print("end")
    }


}

