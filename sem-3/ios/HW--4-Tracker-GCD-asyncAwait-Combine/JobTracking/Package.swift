// swift-tools-version: 5.5

import PackageDescription

let package = Package(
    name: "JobTracking",
    platforms: [.iOS(.v12), .macOS(.v11)],
    products: [
        .library(
            name: "JobTracking",
            targets: ["JobTracking"]
        ),
    ],
    targets: [
        .target(
            name: "JobTracking",
            dependencies: []
        ),
        .testTarget(
            name: "JobTrackingTests",
            dependencies: ["JobTracking"]
        ),
    ]
)
