/**
 * @file Tree-sitter grammar for HErl files
 * @author William Fank Thomé <williamthome@hotmail.com>
 * @license MIT
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "herl",

  rules: {
    // TODO: add the actual grammar rules
    source_file: $ => "hello"
  }
});
