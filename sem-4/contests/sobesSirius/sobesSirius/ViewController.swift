//
//  ViewController.swift
//  sobesSirius
//
//  Created by Grigorii Rassadnikov on 18.04.2023.
//

import UIKit


class ViewController : UIViewController {
    override func viewDidLoad() {
         super.viewDidLoad()
        
        let button : UIButton = {
           let button = UIButton()
            button.setTitle("My button", for: .normal)
            button.backgroundColor = .red
            button.translatesAutoresizingMaskIntoConstraints = false
            return button
        }()
        
        view.addSubview(button)
        NSLayoutConstraint.activate([
            button.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 12),
            button.centerXAnchor.constraint(equalTo: view.centerXAnchor),
        ])
        
        let label : UILabel = {
            let label = UILabel()
            label.text = "Denis"
            label.frame = CGRect(x: 100, y: 100, width: 100, height: 100)
            label.backgroundColor = .green
            return label
        }()
        
        view.addSubview(label)
        
        let imageView: UIImageView = {
            let image = UIImageView()
            image.translatesAutoresizingMaskIntoConstraints = false
            image.backgroundColor = .yellow
            image.image = UIImage(named: "w1")
            return image
        }()
        
        view.addSubview(imageView)
        let const = CGFloat(200)
        NSLayoutConstraint.activate([
            imageView.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            imageView.centerYAnchor.constraint(equalTo: view.centerYAnchor),
            imageView.widthAnchor.constraint(equalToConstant: const),
            imageView.heightAnchor.constraint(equalTo: imageView.widthAnchor, multiplier: (imageView.image?.size.height)! / (imageView.image?.size.width)!)
            
            
        ])
        

        
    }
}
