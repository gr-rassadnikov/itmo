//
//  ActivityView.swift
//  ios-itmo-2022-assignment3
//
//  Created by Grigorii Rassadnikov on 30.12.2022.
//

import Foundation
import SwiftUI

struct ActivityView: UIViewControllerRepresentable {
    

    func makeUIViewController(context: Context) -> UIActivityViewController {
        let vc = UIActivityViewController(activityItems: ["Поделиться фильмом"], applicationActivities: nil)
        return vc
    }
    
    func updateUIViewController(_ uiViewController: UIActivityViewController, context: Context) {

    }
    
    typealias UIViewControllerType = UIActivityViewController
    
    
    
    
}
