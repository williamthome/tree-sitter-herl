// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "TreeSitterHErl",
    products: [
        .library(name: "TreeSitterHErl", targets: ["TreeSitterHErl"]),
    ],
    dependencies: [
        .package(url: "https://github.com/ChimeHQ/SwiftTreeSitter", from: "0.8.0"),
    ],
    targets: [
        .target(
            name: "TreeSitterHErl",
            dependencies: [],
            path: ".",
            sources: [
                "src/parser.c",
                // NOTE: if your language has an external scanner, add it here.
            ],
            resources: [
                .copy("queries")
            ],
            publicHeadersPath: "bindings/swift",
            cSettings: [.headerSearchPath("src")]
        ),
        .testTarget(
            name: "TreeSitterHErlTests",
            dependencies: [
                "SwiftTreeSitter",
                "TreeSitterHErl",
            ],
            path: "bindings/swift/TreeSitterHErlTests"
        )
    ],
    cLanguageStandard: .c11
)
