//
//  File GCDJobTracker.swift
//
//
//  Created by Grigorii Rassadnikov on 18.11.2022.
//

import Combine
import Foundation

public class GCDJobTracker<Key: Hashable, Output, Failure: Error>: CallbackJobTracking {
    private let memoizing: MemoizationOptions
    private let worker: JobWorker<Key, Output, Failure>

    private enum Value {
        case completed(Result<Output, Failure>)
        case run([(Result<Output, Failure>) -> Void])
    }

    private var dict: [Key: Value] = [:]
    private let globalQueueTrack = DispatchQueue.global(qos: .default)
    private let queueTrack = DispatchQueue(label: "queueTrack")

    public func startJob(for key: Key, completion: @escaping (Result<Output, Failure>) -> Void) {
        queueTrack.async { [self] in
            if memoizing.contains(.started) { // хотим использовать трекер
                if let value = dict[key] { // нашли задачу по ключу
                    switch value {
                    case let .completed(result): // задача уже завершилась
                        switch result {
                        case .success:
                            if memoizing.contains(.succeeded) {
                                completion(result)
                            }
                        case .failure:
                            if memoizing.contains(.failed) {
                                completion(result)
                            }
                        }
                    case var .run(array):
                        array.append(completion)
                        dict[key] = Value.run(array)
                    }
                } else { // такой задачи еще не было, создаем ее и запоминаем в []
                    dict[key] = Value.run([completion])
                    globalQueueTrack.async {
                        self.worker(key) { (result: Result<Output, Failure>) in
                            self.queueTrack.async {
                                guard case let .run(array)? = self.dict[key] else { fatalError("Value in dict[\(key)] is't .run, but has just been initialized by .run") }
                                for comletionForApply in array {
                                    comletionForApply(result)
                                }
                                switch self.memoizing {
                                case .failed:
                                    switch result {
                                    case .failure:
                                        self.dict[key] = Value.completed(result)
                                    case .success: // задача завершилась успешно, но ее не надо созранять
                                        self.dict.removeValue(forKey: key)
                                    }
                                case .succeeded:
                                    switch result {
                                    case .failure: // задача завершилась с ошибкой, но ее не надо созранять
                                        self.dict.removeValue(forKey: key)
                                    case .success:
                                        self.dict[key] = Value.completed(result)
                                    }
                                default:
                                    break
                                }
                            }
                        }
                    }
                }
            } else { // вообще не хотим использоватьь трекер и не хотим сохранять задачи
                globalQueueTrack.async {
                    self.worker(key) { (result: Result<Output, Failure>) in
                        self.queueTrack.async {
                            completion(result)
                        }
                    }
                }
            }
        }
    }

    public required init(memoizing: MemoizationOptions, worker: @escaping JobWorker<Key, Output, Failure>) {
        self.memoizing = memoizing
        self.worker = worker
    }
}
