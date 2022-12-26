//
//  CombineJobTracker.swift
//
//
//  Created by Grigorii Rassadnikov on 10.11.2022.
//
import Combine
import Foundation

public class CombineJobTracker<Key: Hashable, Output, Failure: Error>: PublishingJobTracking {
    public typealias JobPublisher = AnyPublisher<Output, Failure>

    public typealias JobPublisherOptional = CurrentValueSubject<Output?, Failure>

    private let memoizing: MemoizationOptions
    private let worker: JobWorker<Key, Output, Failure>

    private var dict: [Key: JobPublisherOptional] = [:]

    private let globalQueueTrack = DispatchQueue.global(qos: .default)
    private let queueTrack = DispatchQueue(label: "queueTrack")

    private func makeSend(for subject: JobPublisherOptional, result: Result<Output, Failure>) {
        switch result {
        case let .success(output):
            subject.send(output)
        case let .failure(error):
            subject.send(completion: .failure(error))
        }
    }

    public func startJob(for key: Key) -> JobPublisher {
        let publisher = JobPublisherOptional(nil)
        if memoizing.contains(.started) { // хотим использовать трекер
            if let dictPublisher = dict[key] { // нашли subject по ключу
                return dictPublisher.compactMap { $0 }.eraseToAnyPublisher()
            } else { // такого subject еще не было, создаем и запоминаем в []
                dict[key] = publisher
                globalQueueTrack.async {
                    self.worker(key) { (result: Result<Output, Failure>) in
                        self.queueTrack.async {
                            switch result {
                            case .success:
                                if self.memoizing.contains(.succeeded) {
                                    self.makeSend(for: publisher, result: result)
                                } else {
                                    self.dict.removeValue(forKey: key)
                                }
                            case .failure:
                                if self.memoizing.contains(.failed) {
                                    self.makeSend(for: publisher, result: result)
                                } else {
                                    self.dict.removeValue(forKey: key)
                                }
                            }
                        }
                    }
                }
            }
        } else { // вообще не хотим использоватьь трекер и не хотим сохранять subjects
            globalQueueTrack.async {
                self.worker(key) { (result: Result<Output, Failure>) in
                    self.queueTrack.async {
                        self.makeSend(for: publisher, result: result)
                    }
                }
            }
        }

        return publisher.compactMap { $0 }.eraseToAnyPublisher()
    }

    public required init(memoizing: MemoizationOptions, worker: @escaping JobWorker<Key, Output, Failure>) {
        self.memoizing = memoizing
        self.worker = worker
    }
}
