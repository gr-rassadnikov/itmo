//
//  Data.swift
//  ios-itmo-2022-assignment3
//
//  Created by Grigorii Rassadnikov on 15.12.2022.
//

import Foundation
import UIKit

class Storage {
    static var user: User? {
        get {
            guard let savedData = UserDefaults.standard.object(forKey: "user") as? Data, let decodedModel = try? NSKeyedUnarchiver.unarchiveTopLevelObjectWithData(savedData) as? User else {
                print("--- W⚠️ : class Storage, can't find savedData, so get nill for user")
                return nil
            }
            return decodedModel
        }
        set {
            let defaults = UserDefaults.standard
            if let user = newValue {
                let key = "user"
                if let savedData = try? NSKeyedArchiver.archivedData(withRootObject: user, requiringSecureCoding: false) {
                    defaults.set(savedData, forKey: key)
                }
            }
        }
    }

    static var tableController: ViewController?

    static var server = Server()
}

func saveImage(imageName: String, image: UIImage) -> String? {
    guard let documentsDirectory = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first else { return nil }

    let fileName = imageName
    let fileURL = documentsDirectory.appendingPathComponent(fileName)
    guard let data = image.jpegData(compressionQuality: 1) else { return nil }

    if FileManager.default.fileExists(atPath: fileURL.path) {
        do {
            try FileManager.default.removeItem(atPath: fileURL.path)
            print("Removed old image")
        } catch let removeError {
            print("couldn't remove file at path", removeError)
        }
    }
    do {
        try data.write(to: fileURL)
    } catch {
        print("error saving file with error", error)
    }
    return fileURL.path
}

func loadImageFromDiskWith(fileName: String) -> UIImage? {
    let documentDirectory = FileManager.SearchPathDirectory.documentDirectory
    let userDomainMask = FileManager.SearchPathDomainMask.userDomainMask
    let paths = NSSearchPathForDirectoriesInDomains(documentDirectory, userDomainMask, true)
    if let dirPath = paths.first {
        let imageUrl = URL(fileURLWithPath: dirPath).appendingPathComponent(fileName)
        let image = UIImage(contentsOfFile: imageUrl.path)
        return image
    }
    return nil
}
