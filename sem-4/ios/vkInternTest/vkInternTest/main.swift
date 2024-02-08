
import Foundation

print("Hello, World!!")

// T-1
//func sayHello(var name: String) {
//    name = name.uppercased()
//    print("HELLO, \(name)")
//}
//
//sayHello("mark")

// T - 2
//let numbers = [1, 2, 3].map{[$0, $0]}
//print(numbers)

//T - 3
//var names = [String]()
//names.append("Mark")
//let name1 = names.removeLast()
//let name2 = names.removeLast()
//print(name2)

//T - 4
//let swiftString: String =  String(describing: String.self)
//print(swiftString)

// T - 5
//let number = Int.max
//let bigNumber = number + 1
//print(bigNumber)

// T - 6
//class Person {
//    var name: String
//
//    override init(initName: String) {
//        self.name = initName
//
//    }
//}
//let person = Person(initName: "Shiny")
//print(person.name)

// T - 7
//protocol Person {
//    var name: String? { get set }
//    var surname: String?
//}

// T - 8
//let i = 2
//
//switch i {
//case 1:
//    print("Result is 1")
//case 2:
//    print("Result is 2")
//case 3:
//    print("Result is 3")
//}

// T - 9
//let errorCode = 300
//switch errorCode {
//case 0..<300:
//    print("1")
//case 300...400:
//    print("2")
//case 0...300:
//    print("3")
//default:
//    print("4")
//}

// T - 10
//let set = Set<String>()
//set.insert("MacOs")


// T - 11
//let name: String?
//print("Hello, \(name)")

// T - 12
//var age: Int!
//print("Age = \(age ?? 20)")

// T - 13
//let days: [String] = ["Tuesday"]
//days.append(contentsOf: ["Monday", "Wednesday"])
//print(days)

// T - 14
//let a = 4
//let b = 3
//var result = 1
//for _ in 1..<b {
//    result*=a
//}
//print(result)

// T - 15
//enum MyEnum {
//    case one
//    case two
//    case three
//}
//
//let value: MyEnum = .two
//switch value {
//case . one:
//    print("hello")
//    fallthrough
//case .two:
//    print("world")
//    fallthrough
//case .three:
//    print("!")
//}

// T - 16
//let languages: [String?] = ["Python", nil, "Swift", nil,nil,"Scala", "Golang", nil]
//let result = languages.fir0st {language -> Bool in
//    return language?.count == 5
//}
//
//print(result)

// T - 17
//var name: String?
//print("Hello \(name)!")

// T - 18
//var age: Int?
//print("Age = \(age ?? 20)")

// T - 30
//var arr1 = [1, 2, 3]
//var arr2 = arr1
//
//arr2.append(4)
//var len = arr1.count
//print(len)


//--------------------------------------
//T - 1
//var name: String? = "John"
//
//switch name {
//case .none:
//    print("hello")
//case .some(let value):
//    print(value)
//}

//T - 2

//T - 3
//var x = [Int]()
////T - 4
//
////T - 5
//let languages: [String?] = ["Python", nil, "Swift", nil,nil,"Kotlin", "Golang"]
//if let lastv = languages.last {
//    print(lastv)
//}
//T - 8
//let swiftString: String =  String(describing: String.self)
//print(swiftString)

//T - 9
//let passwordAccepted: Bool? = false
//
//if !passwordAccepted! {
//    print("Sucess")
//} else {
//    print("Error")
//}

//T - 10
//let numbers: [Int] = [1, 2, nil, 3, 4]
//let result = numbers.filter{$0 > 2}
//print(result)

//T - 11
//var days: [String] = ["Tuesday"]
//days.append(contentsOf: ["Monday", "Wednesday"])
//print(days)


//T - 16
//let value = "d"
//switch value {
//case "a":
//    print("a")
//case "b":
//    print("b")
//case "c":
//    print("c")
//default:
//    print(value)
//}

//T - 18
//var t = [String]()
//t.reserveCapacity(1)
//t.append("w")
//t.append("q")
//t.append("e")
//t.append("r")
//print(t.count)

//T - 21
//for i in stride(from: 1, to: 13, by: 4) {
//    print(i)
//}

// T - 23
//func viewDidLoad() {
//    print("2")
//    DispatchQueue.main.async {
//        print("3")
//        DispatchQueue.main.sync {
//            print("4")
//        }
//        print("5")
//    }
//    print("6")
//}
//print("1")
//viewDidLoad()
//print("7")

//T - 25
//let numbers = [1, 2, 3].flatMap{[$0, $0]}
//print(numbers)
//
//
//let value = "d"
//switch value {
//case "a":
//    print("a")
//case "b":
//    print("b")
//case "c":
//    print("c")
//default:
//    break
//}
//

// T -30


//// View(height)
//UIView.add
//var height = 100
//// change with animate
//height = 200

//protocol Node: class {
//    var value: String{get set}
//}
//class treeNode: Node {
//    var value: String
//}
//
//let p = treeNode(value: "")

//var age: Int?
//print("Age=\(age)")
//
//let name = "Tom"
//
//switch name {
//case "Tom":
//    fallthrough
//case "Bds","dsaf":
//    print("Pilots")
//default:
//    print("fsdf")
//}
//
//enum t:Int {
//    case a = 1
//    case b
//    case c
//    case d
//
//}
//
//let r = t(rawValue: 3)
//print(r)

//let t = ["1":"1", "2":"2"]
//let u = t["23"] ?? "3"
//print(u)

//var a = 2
//for i in -4...4 where i%2 = 0 {
////    print(i)
//    a+=i
//}
//print(a)

//let r: Int = round(7.5)
//print(r)


func set(a: [Int], l:Int, r:Int, value:Int) -> [Int]{
    var a = a
    for i in l..<r {
        a[i] = value
    }
    return a
}

func get(a: [Int], l:Int, r:Int) -> Int{
    var s = 1000000000
    for i in l..<r {
        s = min(s,a[i])
    }
    return s
}

func add(a: [Int], l:Int, r:Int, value:Int) -> [Int]{
    var a = a
    for i in l..<r {
        a[i] += value
    }
    return a
}

var arr = [Int](repeating: 0, count: 12)
arr = add(a: arr, l: 0, r: 4, value: 1)
arr = add(a: arr, l: 8, r: 12, value: 1)
arr = add(a: arr, l: 2, r: 11, value: 2)
arr = add(a: arr, l: 5, r: 8, value: -1)
print(get(a: arr, l: 0, r: 12))
print(get(a: arr, l: 3, r: 4))
print(get(a: arr, l: 4, r: 5))
print(get(a: arr, l: 5, r: 8))





//arr = set(a: arr, l: 0, r: 5, value: 2)
//arr = set(a: arr, l: 5, r: 8, value: 3)
//print(get(a: arr, l: 4, r: 5))
//print(get(a: arr, l: 5, r: 6))
//
//for i in 1...5 {
//    arr = add(a: arr, l: (4*i)%10, r: ((4*i)%10) + 2, value: (i%2) * 2)
//}
//print(get(a: arr, l: 0, r: 10))
//print(get(a: arr, l: 4, r: 6))




//var a = 5
//var x = 2
//while x > a {
//    a = a + x
//    x-=1
//}
//print(a)


//let n = ["A", "B", "C"]
//let result = n.sorted{$1 > $0}
//
//print(result)

//var num: Int = 0
//num++

//var a = 5
//var x = 2
//repeat {
//    a = a + x
//    x -= 1
//} while x > 0
//print(a)
//
//            var age: Int?
//            print("Age = \(age)")

//let a = 5
//let b = 7
//
//print(a>b ? a:b)

//let age = 18
//let isAdult = age >= 18
//print(isAdult ? "1":"2")

//var name: String?
//switch name {
//case .none:
//    print("hello")
//default:
//    print("world")
//}


