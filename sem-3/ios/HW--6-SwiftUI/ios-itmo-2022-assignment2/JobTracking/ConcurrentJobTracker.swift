//
//  ConcurrentJobTracker.swift
//
//
//  Created by Grigorii Rassadnikov on 18.11.2022.
//

import Foundation

public actor ConcurrentJobTracker<Key: Hashable, Output>: AsyncJobTracking {
    public typealias Failure = Error

    private let memoizing: MemoizationOptions
    private let worker: JobWorker<Key, Output, Failure>

    private var dict: [Key: Task<Output, Failure>] = [:]

    private func makeTask(key: Key) -> Task<Output, Failure> {
        return Task<Output, Failure>(priority: .medium) {
            try await withCheckedThrowingContinuation { continuation in
                worker(key) { continuation.resume(with: $0) }
            }
        }
    }

    public func startJob(for key: Key) async throws -> Output {
        let task: Task<Output, Failure>
        if memoizing.contains(.started) {
            if let taskDict = dict[key] {
                task = taskDict
            } else {
                task = makeTask(key: key)
                switch await task.result {
                case .success:
                    if memoizing.contains(.succeeded) {
                        dict[key] = task
                    }
                case .failure:
                    if memoizing.contains(.failed) {
                        dict[key] = task
                    }
                }
            }
        } else {
            task = makeTask(key: key)
        }
        return try await task.value
    }

    public init(memoizing: MemoizationOptions, worker: @escaping JobWorker<Key, Output, Failure>) {
        self.memoizing = memoizing
        self.worker = worker
    }
}
