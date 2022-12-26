import Combine
import Foundation
@testable import JobTracking
import XCTest

final class JobTrackingTests: XCTestCase {
    /* ваши тесты здесь */
    func testGCDFib() {
        enum fibError: Error {
            case badNumber(String) // bad number : >= 20
            case negativeNumber(String)
        }

        @Sendable func fib(number: Int) throws -> Int {
            if number < 0 {
                throw fibError.negativeNumber("Your number is negative")
            }
            if number >= 20 {
                throw fibError.badNumber("Your number is bad (in my theory of the world)")
            }
            if number == 0 {
                return 0
            }
            if number == 1 {
                return 1
            }
            return try fib(number: number - 1) + fib(number: number - 2)
        }

        @Sendable func fibResult(number: Int) -> Result<Int, fibError> {
            do {
                let ans = try fib(number: number)
                return Result<Int, fibError>.success(ans)
            } catch {
                return Result<Int, fibError>.failure(error as! fibError)
            }
        }

        func printer(result: Result<Int, fibError>) {
            switch result {
            case let .success(ans):
                print("Result : \(ans)")
            case let .failure(error):
                print(error)
            }
        }

        @Sendable func workerFib(key: Int, completion: @escaping (Result<Int, fibError>) -> Void) {
            completion(fibResult(number: key))
        }

        print("------------------- TEST TRACKER 1 -----------------")

        let tracker = GCDJobTracker<Int, Int, fibError>(
            memoizing: MemoizationOptions.failed, worker: workerFib
        )

        tracker.startJob(for: 19, completion: printer)
        tracker.startJob(for: 5, completion: printer)
        tracker.startJob(for: -2, completion: printer)
        tracker.startJob(for: 2, completion: printer)
        tracker.startJob(for: 4, completion: printer)
        tracker.startJob(for: 45, completion: printer)
        tracker.startJob(for: 1, completion: printer)

        tracker.startJob(for: 1, completion: printer)
        tracker.startJob(for: 1, completion: printer)
        tracker.startJob(for: 1, completion: printer)
        tracker.startJob(for: 2, completion: printer)
        tracker.startJob(for: 1, completion: printer)
        tracker.startJob(for: 2, completion: printer)

        print("+++++++++++++++++++ TEST TRACKER 1 ++++++++++++++++++")
    }

    func testConcurrentFib() async {
        enum fibError: Error {
            case badNumber(String) // bad number : >= 200
            case negativeNumber(String)
        }

        @Sendable func fib(number: Int) throws -> Int {
            if number < 0 {
                throw fibError.negativeNumber("Your number is negative")
            }
            if number >= 200 {
                throw fibError.badNumber("Your number is bad (in my theory of the world)")
            }
            if number == 0 {
                return 0
            }
            if number == 1 {
                return 1
            }
            return try fib(number: number - 1) + fib(number: number - 2)
        }

        @Sendable func fibResult2(number: Int) -> Result<Int, Error> {
            do {
                let ans = try fib(number: number)
                return Result<Int, Error>.success(ans)
            } catch {
                return Result<Int, Error>.failure(error)
            }
        }

        @Sendable func printer2(key: Int, tracker: ConcurrentJobTracker<Int, Int>) async {
            do {
                let ans = try await tracker.startJob(for: key)
                print("Result for \(key): \(ans)")
            } catch {
                print(error)
            }
        }

        @Sendable func workerFib2(key: Int, completion: @escaping (Result<Int, Error>) -> Void) {
            completion(fibResult2(number: key))
        }

        print("------------------- TEST TRACKER 2 -----------------")

        let concurrentTracker = ConcurrentJobTracker<Int, Int>(
            memoizing: MemoizationOptions.completed, worker: workerFib2
        )

        async let clj1: () = printer2(key: 18, tracker: concurrentTracker)
        async let clj2: () = printer2(key: 8, tracker: concurrentTracker)
        async let clj3: () = printer2(key: 1, tracker: concurrentTracker)
        async let clj4: () = printer2(key: 28, tracker: concurrentTracker)
        let _ = await [clj1, clj2, clj3, clj4]

        do {
            let ans = try await concurrentTracker.startJob(for: 1)
            print("Result for 1: \(ans)")
        } catch {
            print(error)
        }

        do {
            let ans = try await concurrentTracker.startJob(for: 26)
            print("Result for 26: \(ans)")
        } catch {
            print(error)
        }

        print("+++++++++++++++++++ TEST TRACKER 2 ++++++++++++++++++")
    }

    func testCombineFib() {
        enum fibError: Error {
            case badNumber(String) // bad number : >= 20
            case negativeNumber(String)
        }

        @Sendable func fib(number: Int) throws -> Int {
            if number < 0 {
                throw fibError.negativeNumber("Your number is negative")
            }
            if number >= 20 {
                throw fibError.badNumber("Your number is bad (in my theory of the world)")
            }
            if number == 0 {
                return 0
            }
            if number == 1 {
                return 1
            }
            return try fib(number: number - 1) + fib(number: number - 2)
        }

        @Sendable func fibResult(number: Int) -> Result<Int, fibError> {
            do {
                let ans = try fib(number: number)
                return Result<Int, fibError>.success(ans)
            } catch {
                return Result<Int, fibError>.failure(error as! fibError)
            }
        }

        func printer(result: Result<Int, fibError>) {
            switch result {
            case let .success(ans):
                print("Result : \(ans)")
            case let .failure(error):
                print(error)
            }
        }

        @Sendable func workerFib(key: Int, completion: @escaping (Result<Int, fibError>) -> Void) {
            completion(fibResult(number: key))
        }

        print("------------------- TEST TRACKER 3 -----------------")

        let tracker = CombineJobTracker<Int, Int, fibError>(
            memoizing: MemoizationOptions.completed, worker: workerFib
        )
        let subject1 = tracker.startJob(for: 21)
        let subject2 = tracker.startJob(for: 13)
        let subject3 = tracker.startJob(for: 11)

        // we don't sleep, sometimes worker was fast and was running makeSend, sometis else..
        subject1.sink { completion in
            switch completion {
            case let .failure(error):
                print("Error at CombineTracker: \(error)")
            case .finished:
                print("Result for finish 21: ")
            }
        } receiveValue: { ans in
            print("Result for 21: \(ans)")
        }

        let subject4 = tracker.startJob(for: 23)

        let subject6 = tracker.startJob(for: 2)

        // sleep))

        var sleep = 0
        for _ in 0 ..< 1_000_000 {
            sleep += 1
        }

        let subject5 = tracker.startJob(for: 11)

        subject1.sink { completion in
            switch completion {
            case let .failure(error):
                print("Error at CombineTracker: \(error)")
            case .finished:
                print("Result for finish 21: ")
            }
        } receiveValue: { ans in
            print("Result for 21: \(ans)")
        }

        subject2.sink { completion in
            switch completion {
            case let .failure(error):
                print("Error at CombineTracker: \(error)")
            case .finished:
                print("Result for finish 13: ")
            }
        } receiveValue: { ans in
            print("Result for 13: \(ans)")
        }

        subject3.sink { completion in
            switch completion {
            case let .failure(error):
                print("Error at CombineTracker: \(error)")
            case .finished:
                print("Result for finish 11: ")
            }
        } receiveValue: { ans in
            print("Result for 11: \(ans)")
        }

        subject4.sink { completion in
            switch completion {
            case let .failure(error):
                print("Error at CombineTracker: \(error)")
            case .finished:
                print("Result for finish 23: ")
            }
        } receiveValue: { ans in
            print("Result for 23: \(ans)")
        }

        subject5.sink { completion in
            switch completion {
            case let .failure(error):
                print("Error at CombineTracker: \(error)")
            case .finished:
                print("Result for finish 11: ")
            }
        } receiveValue: { ans in
            print("Result for 11: \(ans)")
        }

        subject6.sink { completion in
            switch completion {
            case let .failure(error):
                print("Error at CombineTracker: \(error)")
            case .finished:
                print("Result for finish 2: ")
            }
        } receiveValue: { ans in
            print("Result for 2: \(ans)")
        }

        print("+++++++++++++++++++ TEST TRACKER 3 ++++++++++++++++++")
    }
}
