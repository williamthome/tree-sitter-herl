/**
 * @file Tree-sitter grammar for HErl files
 * @author William Fank Thomé <williamthome@hotmail.com>
 * @license MIT
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "herl",

  externals: $ => [$.expression],

  rules: {
    tokens: $ => repeat(choice(
      $._expression,
      $.text,
    )),

    _expression: $ => seq(
      '{',
      $.expression,
      '}'
    ),

    text: _$ => /[^{]+/,
  },
});
