import Foundation


//@MainActor class ImportantEntity: ObservableObject {
//    func runSomeRequest () async {
//        print ("дактиль")
//        await MainActor.run {
//            print("анапест")
//            Task { @MainActor in
//                print("амфибрахий")
//            }
//            print("хорей")
//        }
//        print("ямб")
//    }
//}
//
//
//
//await ImportantEntity().runSomeRequest()

//func setPriceLabelText(price: Int) {
//    if price <= 0 {
//        assertionFailure ("Price value should be positive!")
//    }
////    somePriceLabel.text = "\(price)"
//}
//
//setPriceLabelText(price: -10)
import SwiftUI


//final class Presenter {
////    private let view = Button(.cancel)
//    deinit {
////        view.removeFromSuperview()
//    }
//}
//
//actor TaskPerformer {
//    func perform(task: () -> Void) async {
//        // do some work
//        await MainActor.run {
//            task()
//        }
//    }
//}
//
//final class Runner {
//    private let t = TaskPerformer ()
//    private var p: Presenter? = Presenter ( )
//    func run()  {
//        let task = { [p] in
//            print (String (describing: p!))
//        }
//        p = nil
//        Task {
//            await t.perform(task: task)
//        }
//    }
//}
//
//Runner().run()

//enum Color {
//    case red
//    case green
//}
//
//let s = Set<Color>()
//s.insert(.green)

import Combine
import PlaygroundSupport
import SwiftUI
import UIKit
 
struct Book: Codable, Identifiable {
  let id, title, author: String
 
  init(from openLibraryBook: BookSearchResultBook) {
    self.id = openLibraryBook.key ?? UUID().uuidString
    self.title = openLibraryBook.title ?? ""
    self.author = openLibraryBook.authorName?[0] ?? ""
  }
}
 
struct BookSearchResult: Codable {
  let books: [BookSearchResultBook]?
  enum CodingKeys: String, CodingKey {
    case books = "docs"
  }
}
 
struct BookSearchResultBook: Codable {
  let key, title: String?
  let authorName: [String]?
 
  enum CodingKeys: String, CodingKey {
    case title
    case authorName = "author_name"
    case key
  }
}
 
struct BookSearchRowView: View {
  var book: Book
  var body: some View {
    VStack(alignment: .leading) {
      Text(book.title)
        .font(.headline)
      Text("by \(book.author)")
        .font(.subheadline)
    }
  }
}
 
class ViewModel: ObservableObject {
  @Published
  var terms: String = ""
 
  // [1]
  private(set) var result: [Book] = []
 
  // [2]
  var isSearching = false
 
  private var cancellables = Set<AnyCancellable>()
 
  init() {
    $terms
      .dropFirst()
      // [3]
      .removeDuplicates()
      .handleEvents {
        // [4]
      }
      .await { terms in
        // [5]
      }
      .receive(on: DispatchQueue.main)
      .eraseToAnyPublisher()
      .handleEvents {
        // [6]
      }
      // [7]
  }
 
  private func doSearch(matching terms: String) async -> [Book] {
    let escapedTerms = terms.addingPercentEncoding(withAllowedCharacters: .urlHostAllowed) ?? ""
    let url = URL(string: "https://openlibrary.org/search.json?q=\(escapedTerms)")!
    do {
      // [8]
      // [9]
      return result.books?.compactMap { Book(from: $0) } ?? []
    }
    catch {
      return []
    }
  }
}
 
struct BookSearchView: View {
  // [10]
  fileprivate var viewModel = ViewModel()
 
  var body: some View {
    List(viewModel.result) { book in
      // [11]
    }
    .overlay {
      if viewModel.isSearching {
        // [12]
      }
    }
    .navigationTitle("Open Library")
    .searchable(text: $viewModel.terms)
  }
}
 
extension Publisher {
  func ‘await‘<T>(_ transform: @escaping (Output) async -> T)
      -> AnyPublisher<T, Failure> {
    flatMap { value -> Future<T, Failure> in
      Future { promise in
        Task {
          // [13]
          promise(.success(result))
        }
      }
    }
    // [14]
  }
 
  func handleEvents(_ receiveOutput: (@escaping (Self.Output) -> Void))
      -> Publishers.HandleEvents<Self> {
    self.handleEvents(receiveOutput: receiveOutput)
  }
 
  func handleEvents(_ receiveOutput: (@escaping () -> Void))
      -> Publishers.HandleEvents<Self> {
    self.handleEvents { output in
      receiveOutput()
    }
  }
}
 
let navigationViewController = UINavigationController(
  rootViewController:
    // [15]
  )
navigationViewController.view.frame = CGRect(x: 0, y: 0, width: 320, height: 568)
PlaygroundPage.current.liveView = navigationViewController
Каждый пропуск вида // [X] — это одна из конструкций списка:
self.isSearching = false
let result = await transform(value)
await self.doSearch(matching: terms)
BookSearchRowView(book: book)
.eraseToAnyPublisher()
let result = try JSONDecoder().decode(BookSearchResult.self, from: data)
@Published
let (data, _) = try await URLSession.shared.data(from: url)
@StateObject
ProgressView()
.assign(to: &$result)
UIHostingController(rootView: BookSearchView())
@Published
.debounce(for: .seconds(1), scheduler: DispatchQueue.main)
self.isSearching = true  
