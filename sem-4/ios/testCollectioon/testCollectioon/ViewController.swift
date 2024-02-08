//
//  ViewController.swift
//  testCollectioon
//
//  Created by Grigorii Rassadnikov on 08.05.2023.
//

import UIKit

class ViewController: UIViewController, UICollectionViewDelegate, UICollectionViewDataSource, UICollectionViewDelegateFlowLayout {
    
    private let cv = UICollectionView(frame: .zero,
    collectionViewLayout: UICollectionViewFlowLayout())

    override func viewDidLoad() {
        super.viewDidLoad()
        cv.register(MyCell.self, forCellWithReuseIdentifier: MyCell.ind)
        cv.delegate = self
        cv.dataSource = self
        cv.translatesAutoresizingMaskIntoConstraints = false
        
        view.addSubview(cv)
        
        NSLayoutConstraint.activate([
            cv.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor),
            cv.heightAnchor.constraint(equalToConstant: 800),
            cv.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 4),
            cv.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -4)
        ])
    }
    
    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        //cv.frame = view.bounds
    }
    
}

