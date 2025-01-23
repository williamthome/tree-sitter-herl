import XCTest
import SwiftTreeSitter
import TreeSitterHErl

final class TreeSitterHErlTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_herl())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading HErl grammar")
    }
}
