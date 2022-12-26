//
//  User.swift
//  ios-itmo-2022-assignment3
//
//  Created by Grigorii Rassadnikov on 15.12.2022.
//

import Foundation
import UIKit

class User: NSObject, NSCoding {
    func encode(with coder: NSCoder) {
        coder.encode(login, forKey: "login")
        coder.encode(password, forKey: "password")
        coder.encode(mail, forKey: "mail")
        coder.encode(token, forKey: "token")
        coder.encode(id, forKey: "id")
    }

    required init?(coder: NSCoder) {
        login = coder.decodeObject(forKey: "login") as? String ?? ""
        password = coder.decodeObject(forKey: "password") as? String ?? ""
        mail = coder.decodeObject(forKey: "mail") as? String ?? ""
        token = coder.decodeObject(forKey: "token") as? String ?? ""
        id = coder.decodeObject(forKey: "id") as? String ?? ""
    }

    var login: String
    var password: String
    var mail: String
    var token: String
    var id: String

    init(login: String, password: String, mail: String, token: String, id: String) {
        self.login = login
        self.password = password
        self.mail = mail
        self.token = token
        self.id = id
    }
}
