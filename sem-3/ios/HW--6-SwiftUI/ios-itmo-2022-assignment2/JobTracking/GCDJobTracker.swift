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
            if memoizing.contains(.started) {
                if let value = dict[key] {
                    switch value {
                    case let .completed(result):
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
                } else {
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
                                    case .success:
                                        self.dict.removeValue(forKey: key)
                                    }
                                case .succeeded:
                                    switch result {
                                    case .failure:
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
            } else {
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
