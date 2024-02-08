//
//  MyCell.swift
//  testCollectioon
//
//  Created by Grigorii Rassadnikov on 08.05.2023.
//

import UIKit

class MyCell: UICollectionViewCell {
    static let ind = "MyCell"
    
    private let imageView: UIImageView = {
        let image = UIImageView()
        image.contentMode = .scaleAspectFill
        image.clipsToBounds = true
        return image
        
    }()
    
    func showX() {
        imageView.backgroundColor = .blue
    }
    
    func showO() {
        imageView.backgroundColor = .red
    }
    
    func showE() {
        imageView.backgroundColor = .gray
    }
    
    
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        contentView.addSubview(imageView)
        
      
        //imageView.image = UIImage(named: "image1")
        imageView.layer.cornerRadius = 10
        imageView.layer.borderColor = UIColor.green.cgColor
        imageView.layer.borderWidth = 4
        showE()
        
        
    }
    
    required init?(coder: NSCoder) {
        fatalError()
    }
    
    override func layoutSubviews() {
        super.layoutSubviews()
        imageView.frame = contentView.bounds
    }
    
    override func prepareForReuse() {
        super.prepareForReuse()
        imageView.image = nil
    }
}


