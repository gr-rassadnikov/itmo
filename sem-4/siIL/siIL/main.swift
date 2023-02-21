

import Foundation

//------------A---------------
//struct Person {
//    enum Gender {
//        case male
//        case female
//    }
//
//    let name: String
//    let surname: String
//    let age: Int
//    let gender: Gender
//}
//
//
//let listOfPersons: [Person] = [
//    .init(name: "Paul", surname: "Brown", age: 23, gender: .male),
//    .init(name: "John", surname: "Williams", age: 5, gender: .male),
//    .init(name: "Donna", surname: "Anderson", age: 62, gender: .male),
//    .init(name: "Jessica", surname: "Richards", age: 17, gender: .male),
//    .init(name: "Martin", surname: "Scott", age: 33, gender: .male),
//    .init(name: "Scott", surname: "Martin", age: 33, gender: .female),
//    .init(name: "Eva", surname: "Peters", age: 17, gender: .female),
//    .init(name: "Emily", surname: "Gibson", age: 11, gender: .female),
//    .init(name: "Mia", surname: "Jordan", age: 97, gender: .female),
//    .init(name: "Sofia", surname: "Grant", age: 8, gender: .female),
//    .init(name: "Olivia", surname: "Davis", age: 52, gender: .female),
//    .init(name: "Mia", surname: "Jones", age: 83, gender: .female),
//    .init(name: "Olivia", surname: "Davis", age: 24, gender: .female),
//]
//
//extension Person: Hashable {
//    func hash(into hasher : inout Hasher) {
//        let combined = name.hashValue ^ surname.hashValue
//        hasher.combine(combined)
//    }
    
//    func hash(into hasher : inout Hasher) {
//        hasher.combine(name)
//        hasher.combine(surname)
//    }
    
//    func hash(into hasher : inout Hasher) { +++
//          hasher.combine(age)
//          hasher.combine(gen)
//      }
    
//    func hash(into hasher : inout Hasher) {
//        let combined = name.unicodeScalars.map {
//            Int($0.value)
//        }.reduce(0, +)+age
//
//        hasher.combine(combined)
//      }
    
//    func hash(into hasher : inout Hasher) { +++
//        hasher.combine(name.count)
//        hasher.combine(surname.count)
//        hasher.combine(age)
//      }
    
//    func hash(into hasher : inout Hasher) {
//        let combined = name.count + surname.count + age
//        hasher.combine(combined)
//      }
//}
//
//var hasher = Hasher()
//listOfPersons.forEach({
//    hasher = Hasher()
//    $0.hash(into: &hasher)
//    print(hasher.finalize())
//})
    
//---------D-------------
    
//let session = URLSession(configuration: URLSessionConfiguration.default)
//    
//let url = URL(string: "https://newsapi.org/v2/everything?q=tesla&from=2023-01-12&sortBy=publishedAt&apiKey=1566fd5ff62348f1b2eee00213a4c4ac")
//
//let task = session.dataTask(with: url!) { data, _, error in
//    guard let data = data else {
//            print("❌")
//            print(error as Any)
//        return
//    }
//            let json = try? JSONSerialization.jsonObject(with: data, options: JSONSerialization.ReadingOptions.allowFragments)
//            print(json)
//            print("st")
//        
//}
//task.resume()
//
//print("end")

//       let configuration = URLSessionConfiguration.default
//// собственная сессия
//       let session =  URLSession(configuration: configuration)
//
//// создаем url из строки
//       let url = URL(string: "https://newsapi.org/v2/everything?q=tesla&from=2023-01-12&sortBy=publishedAt&apiKey=1566fd5ff62348f1b2eee00213a4c4ac")
//
//// задача для запуска
//       let task = session.dataTask(with: url!) { (data, response, error) in
//// в замыкании данные, полученные от сервера, мы преобразуем в json
//           let json = try? JSONSerialization.jsonObject(with: data!, options: JSONSerialization.ReadingOptions.allowFragments)
//// выводим в консоль
//           print(json)
//       }
//// запускаем задачу
//       task.resume()

//--------------------------------

struct Structure: Equatable {
    static func == (lhs: Structure, rhs: Structure) -> Bool {
        return lhs.title == rhs.title
    }
    let title: String

    var closures = [(() -> ())?]()

    mutating func addClosure(_ c: (() -> ())?) {
        self.closures.append(c)
    }
}

var a =  Structure(title: "a")
let b = Structure(title: "a")
print(a==b)
a.addClosure({ print("e")
    return })
a.addClosure(nil)
a.closures[1]


// --------I------------

//func dfs(v: Int, h : Int){
//    res[v] = h
//    for i in g[v] {
//        dfs(v: i, h: h+1)
//    }
//}
//
//let n = Int(readLine()!)!
//var res =  Array(repeating: 0, count: n)
//var p : [Int] = (readLine()?.split(separator: " ").map({Int($0)!}))!
//
//var g : [[Int]] = []
//
//var ind = 1
//for i in p {
//    if i == 0 {
//        break
//    }
//    ind+=1
//}
//
//for i in 0...n-1 {
//    g.append([])
//}
//
//for i in 0...n-1 {
//    if p[i]==0{
//        continue
//    }
//    g[p[i]-1].append(i)
//}
//dfs(v: ind-1, h: 0)
//res.forEach({print($0, terminator: " ")})


