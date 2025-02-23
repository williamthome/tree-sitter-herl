#include "tree_sitter/alloc.h"
#include "tree_sitter/parser.h"
#include <stdint.h>
#include <string.h>

typedef enum { EXPRESSION } TokenType;

typedef struct {
  unsigned nested_level;
} Scanner;

static inline void advance(TSLexer *lexer) { lexer->advance(lexer, false); }

static inline void skip(TSLexer *lexer) { lexer->advance(lexer, true); }

static inline void skip_string(TSLexer *lexer) {
  while (lexer->lookahead && lexer->lookahead != '\\' &&
         lexer->lookahead != '"') {
    if (lexer->lookahead == '\\') {
      advance(lexer);
      if (lexer->lookahead == '"') {
        advance(lexer);
      }
      return skip_string(lexer);
    } else {
      advance(lexer);
      return skip_string(lexer);
    }
  }
  advance(lexer);
}

static inline void skip_atom(TSLexer *lexer) {
  while (lexer->lookahead && lexer->lookahead != '\\' &&
         lexer->lookahead != '\'') {
    if (lexer->lookahead == '\\') {
      advance(lexer);
      if (lexer->lookahead == '\'') {
        advance(lexer);
      }
      return skip_atom(lexer);
    } else {
      advance(lexer);
      return skip_atom(lexer);
    }
  }
  advance(lexer);
}

static unsigned serialize(Scanner *scanner, char *buffer) {
  unsigned nested_level = scanner->nested_level;
  unsigned size = sizeof(nested_level);
  memcpy(&buffer[size], &nested_level, sizeof(nested_level));
  size = sizeof(nested_level);
  return size;
}

static void deserialize(Scanner *scanner, const char *buffer, unsigned length) {
  return;
}

static bool scan_expression(Scanner *scanner, TSLexer *lexer) {
  // Scan until we find the closing curly brace or another significant character
  while (lexer->lookahead && lexer->lookahead != '{' &&
         lexer->lookahead != '}' && lexer->lookahead != '"' &&
         lexer->lookahead != '\'') {
    advance(lexer);
  }

  if (lexer->lookahead == '{') {
    // Opening brace found; increase nesting level
    scanner->nested_level++;
    advance(lexer);
    return scan_expression(scanner, lexer);
  } else if (lexer->lookahead == '}') {
    // Closing brace found; decrease nesting level or complete expression
    if (scanner->nested_level == 0) {
      // The latest opening brace was found; reset and return
      scanner->nested_level = 0;
      // Mark the end of the valid expression
      lexer->mark_end(lexer);
      lexer->result_symbol = EXPRESSION;
      return true;
    } else {
      // Not the latest opening brace; decrease nesting level
      scanner->nested_level--;
      advance(lexer);
      return scan_expression(scanner, lexer);
    }
  } else if (lexer->lookahead == '"') {
    // Handle strings
    advance(lexer);
    skip_string(lexer);
    return scan_expression(scanner, lexer);
  } else if (lexer->lookahead == '\'') {
    // Handle atoms
    advance(lexer);
    skip_atom(lexer);
    return scan_expression(scanner, lexer);
  }

  // If no valid content is found, return false
  return false;
}

static bool scan(Scanner *scanner, TSLexer *lexer, const bool *valid_symbols) {
  if (valid_symbols[EXPRESSION] && scan_expression(scanner, lexer)) {
    return true;
  }
  return false;
}

void *tree_sitter_herl_external_scanner_create() {
  Scanner *scanner = (Scanner *)ts_calloc(1, sizeof(Scanner));
  return scanner;
}

bool tree_sitter_herl_external_scanner_scan(void *payload, TSLexer *lexer,
                                            const bool *valid_symbols) {
  Scanner *scanner = (Scanner *)payload;
  return scan(scanner, lexer, valid_symbols);
}

unsigned tree_sitter_herl_external_scanner_serialize(void *payload,
                                                     char *buffer) {
  Scanner *scanner = (Scanner *)payload;
  return serialize(scanner, buffer);
}

void tree_sitter_herl_external_scanner_deserialize(void *payload,
                                                   const char *buffer,
                                                   unsigned length) {
  Scanner *scanner = (Scanner *)payload;
  deserialize(scanner, buffer, length);
}

void tree_sitter_herl_external_scanner_destroy(void *payload) {
  Scanner *scanner = (Scanner *)payload;
  ts_free(scanner);
}
