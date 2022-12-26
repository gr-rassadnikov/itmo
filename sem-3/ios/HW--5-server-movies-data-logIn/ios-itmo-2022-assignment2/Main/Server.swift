//
//  Server.swift
//  ios-itmo-2022-assignment3
//
//  Created by Grigorii Rassadnikov on 22.12.2022.
//

import Foundation
import UIKit

class Server {
    private let urlHttp = "http://127.0.0.1:3131/"
    private let urlLogin = "http://127.0.0.1:3131/auth/login"
    private let urlRegister = "http://127.0.0.1:3131/auth/register"
    private let urlImageUpload = "http://127.0.0.1:3131/image/upload"
    private let urlImage = "http://127.0.0.1:3131/image/"
    private let urlMovies = "http://127.0.0.1:3131/movies/?cursor=30&count=30"
    private let urlMovie = "http://127.0.0.1:3131/movies/"

    private let session = URLSession(configuration: URLSessionConfiguration.default)
    private let decoder = JSONDecoder()

    func loginRequest(login: String, password: String, mail: String,
                      comletion: @escaping (PostEnterBody) -> Void)
    {
        let urlConstructor = URLComponents(string: urlLogin)
        var request = URLRequest(url: (urlConstructor?.url!)!)

        request.httpMethod = "POST"
        request.setValue("application/json; charset=UTF-8", forHTTPHeaderField: "Content-type")

        let jsonBody: [String: Any] = [
            "login": login,
            "password": password,
            "email": mail,
        ]

        request.httpBody = try! JSONSerialization.data(withJSONObject: jsonBody)
        let task = session.dataTask(with: request) { data, _, error in
            guard let data = data else {
                print("❌ loginRequest: data is nil")
                print(error as Any)
                return
            }
            do {
                let result = try self.decoder.decode(PostEnterBody.self, from: data)
                DispatchQueue.main.async {
                    comletion(result)
                }
            } catch {
                print("🆘 bad code, loginRequest, can't decode data to PostEnterBody and make copmletion")
            }
        }
        task.resume()
    }

    func registerRequest(login: String, password: String, mail: String,
                         comletion: @escaping (PostEnterBody) -> Void)
    {
        let urlConstructor = URLComponents(string: urlRegister)
        var request = URLRequest(url: (urlConstructor?.url!)!)

        request.httpMethod = "POST"
        request.setValue("application/json; charset=UTF-8", forHTTPHeaderField: "Content-type")

        let jsonBody: [String: Any] = [
            "login": login,
            "password": password,
            "email": mail,
        ]

        request.httpBody = try! JSONSerialization.data(withJSONObject: jsonBody)
        let task = session.dataTask(with: request) { data, _, error in
            guard let data = data else {
                print("❌ registerRequest: data is nil")
                print(error as Any)
                return
            }
            do {
                let resultReg = try self.decoder.decode(PostRegisterBody.self, from: data)
                if resultReg.error == 0 {
                    self.loginRequest(login: login, password: password, mail: mail, comletion: comletion)
                } else {
                    print("❌ error with register user:")
                    print(resultReg.message)
                }
            } catch {
                print("🆘 bad code, registerRequest, can't decode data to PostRegisterBody and make copmletion")
            }
        }
        task.resume()
    }

    func listMoviesRequest(token _: String, completion: @escaping ([Movie]) -> Void) {
        let urlConstructor = URLComponents(string: urlMovies)
        var request = URLRequest(url: (urlConstructor?.url!)!)

        request.httpMethod = "GET"
        request.setValue("Bearer \(Storage.user!.token)", forHTTPHeaderField: "Authorization")
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")

        let task = session.dataTask(with: request) { data, _, error in
            guard let data = data else {
                print("❌ listMoviesRequest: data is nil")
                print(error as Any)
                return
            }

            let decoderMovie = JSONDecoder()
            decoderMovie.keyDecodingStrategy = .convertFromSnakeCase
            let result = try! decoderMovie.decode(MovieContainer.self, from: data)
            DispatchQueue.main.async {
                completion(result.movies)
            }
        }
        task.resume()
    }

    func postMovieRequest(title: String, director: String, date: Int, raiting: Int, posterId: String, createdAt: Int? = nil,
                          comletiom: @escaping (Int) -> Void)
    {
        let urlConstructor = URLComponents(string: urlMovies)
        var request = URLRequest(url: (urlConstructor?.url!)!)

        request.httpMethod = "POST"
        request.setValue("Bearer \(Storage.user!.token)", forHTTPHeaderField: "Authorization")
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")

        let jsonBody: [String: [String: Any?]] = [
            "movie": [
                "title": title,
                "director": director,
                "relise_date": date,
                "rating": raiting,
                "poster_id": posterId,
                "created_at": createdAt,
            ],
        ]

        request.httpBody = try! JSONSerialization.data(withJSONObject: jsonBody)
        let task = session.dataTask(with: request) { data, _, error in
            guard let data = data else {
                print("❌ postMovieRequest: data is nil")
                print(error as Any)
                return
            }
            do {
                let decoderMovie = JSONDecoder()
                decoderMovie.keyDecodingStrategy = .convertFromSnakeCase
                let result = try decoderMovie.decode(GetMovieBody.self, from: data)
                DispatchQueue.main.async {
                    comletiom(result.id)
                }
            } catch {
                print("🆘 bad code, postImageRequest, can't decode data to poster_id and make copmletion")
            }
        }
        task.resume()
    }

    func deleteMovieRequest(movieId: Int) {
        let urlConstructor = URLComponents(string: urlMovie + String(movieId))
        var request = URLRequest(url: (urlConstructor?.url!)!)

        request.httpMethod = "DELETE"
        request.setValue("Bearer \(Storage.user!.token)", forHTTPHeaderField: "Authorization")

        let task = session.dataTask(with: request) { data, _, error in
            if data == nil {
                print("❌ postMovieRequest: data is nil")
                print(error as Any)
                return
            }
        }
        task.resume()
    }

    func changeMovieRequest(movieId: Int, title: String, director: String, date: Int, raiting: Int, posterId: String, createdAt _: Int? = nil, comletiom: @escaping (Int) -> Void)
    {
        deleteMovieRequest(movieId: movieId)
        postMovieRequest(title: title, director: director, date: date, raiting: raiting, posterId: posterId, comletiom: comletiom)
    }

    func postImageRequest(image: UIImage, completion: @escaping (String) -> Void) {
        let urlConstructor = URLComponents(string: urlImageUpload)
        var request = URLRequest(url: (urlConstructor?.url!)!)

        request.httpMethod = "POST"
        request.setValue("Bearer \(Storage.user!.token)", forHTTPHeaderField: "Authorization")
        request.setValue("image/jpeg", forHTTPHeaderField: "Content-Type")
        request.httpBody = image.pngData()

        let task = session.dataTask(with: request) { data, _, error in
            guard let data = data else {
                print("❌ postImageRequest: data is nil")
                print(error as Any)
                return
            }
            do {
                let decoderMovie = JSONDecoder()
                decoderMovie.keyDecodingStrategy = .convertFromSnakeCase
                let result = try decoderMovie.decode(PostImageBody.self, from: data)
                if result.error != 0 {
                    print("❌ error to post Image at server:")
                    print(result.message)
                }
                DispatchQueue.main.async {
                    completion(result.posterId)
                }

            } catch {
                print("🆘 bad code, postImageRequest, can't decode data to poster_id and make copmletion")
            }
        }
        task.resume()
    }

    func getImageRequest(posterId: String, completion: @escaping (UIImage) -> Void) {
        let urlConstructor = URLComponents(string: urlImage + posterId)
        var request = URLRequest(url: (urlConstructor?.url!)!)

        request.httpMethod = "GET"
        request.setValue("Bearer \(Storage.user!.token)", forHTTPHeaderField: "Authorization")

        let task = session.dataTask(with: request) { data, _, error in
            guard let data = data else {
                print("❌ getImageRequest: data is nil")
                print(error as Any)
                return
            }
            if let result = UIImage(data: data) {
                DispatchQueue.main.async {
                    completion(result)
                }
            } else {
                print("🆘 bad code, getImageRequest, can't decode data to UIImage and make copmletion")
            }
        }
        task.resume()
    }
}

struct PostEnterBody: Decodable {
    let username: String
    let id: String
    let email: String
    let token: String
    let error: Int
    let message: String

    enum CodingKeys: String, CodingKey {
        case data
        case error
        case message
    }

    enum DataCodingKeys: String, CodingKey {
        case token
        case user
    }

    enum UserCodingKeys: String, CodingKey {
        case email
        case id
        case username
    }

    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)

        message = try container.decode(String.self, forKey: .message)
        error = try container.decode(Int.self, forKey: .error)

        let dataContainer = try container.nestedContainer(keyedBy: DataCodingKeys.self, forKey: .data)
        token = try dataContainer.decode(String.self, forKey: .token)

        let userContainer = try dataContainer.nestedContainer(keyedBy: UserCodingKeys.self, forKey: .user)
        email = try userContainer.decode(String.self, forKey: .email)
        username = try userContainer.decode(String.self, forKey: .username)
        id = try userContainer.decode(String.self, forKey: .id)
    }
}

struct PostRegisterBody: Decodable {
    let data: String?
    let error: Int
    let message: String

    enum CodingKeys: String, CodingKey {
        case data
        case error
        case message
    }

    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)
        message = try container.decode(String.self, forKey: .message)
        error = try container.decode(Int.self, forKey: .error)
        data = try? container.decode(String.self, forKey: .data)
    }
}

struct Movie: Decodable {
    let createdAt: Int
    let id: Int
    let director: String
    let posterId: String
    let rating: Int
    let reliseDate: Int
    let title: String
}

struct MovieContainer: Decodable {
    let movies: [Movie]
}

extension MovieContainer {
    enum CodingKeys: String, CodingKey {
        case data
        enum DataKeys: String, CodingKey {
            case movies
        }
    }

    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)

        let dataContainer = try container.nestedContainer(keyedBy: CodingKeys.DataKeys.self, forKey: .data)
        movies = try dataContainer.decode([Movie].self, forKey: .movies)
    }
}

struct GetMovieBody: Decodable {
    let createdAt: Int
    let id: Int
    let director: String
    let posterId: String
    let rating: Int
    let reliseDate: Int
    let title: String
    let error: Int
    let message: String

    enum CodingKeys: String, CodingKey {
        case data
        case error
        case message
    }

    enum DataCodingKeys: String, CodingKey {
        case movie
    }

    enum MoviesCodingKeys: CodingKey {
        case createdAt
        case id
        case director
        case posterId
        case rating
        case reliseDate
        case title
    }

    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)

        message = try container.decode(String.self, forKey: .message)
        error = try container.decode(Int.self, forKey: .error)
        let dataContainer = try container.nestedContainer(keyedBy: DataCodingKeys.self, forKey: .data)
        let moviesContainer = try dataContainer.nestedContainer(keyedBy: MoviesCodingKeys.self, forKey: .movie)

        createdAt = try moviesContainer.decode(Int.self, forKey: .createdAt)
        id = try moviesContainer.decode(Int.self, forKey: .id)
        director = try moviesContainer.decode(String.self, forKey: .director)
        posterId = try moviesContainer.decode(String.self, forKey: .posterId)
        rating = try moviesContainer.decode(Int.self, forKey: .rating)
        reliseDate = try moviesContainer.decode(Int.self, forKey: .reliseDate)
        title = try moviesContainer.decode(String.self, forKey: .title)
    }
}

struct PostImageBody: Decodable {
    let posterId: String
    let error: Int
    let message: String

    enum CodingKeys: String, CodingKey {
        case data
        case error
        case message
    }

    enum DataCodingKeys: String, CodingKey {
        case posterId
    }

    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)

        message = try container.decode(String.self, forKey: .message)
        error = try container.decode(Int.self, forKey: .error)

        let dataContainer = try container.nestedContainer(keyedBy: DataCodingKeys.self, forKey: .data)
        posterId = try dataContainer.decode(String.self, forKey: .posterId)
    }
}
