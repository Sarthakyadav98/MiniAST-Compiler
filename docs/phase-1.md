# Phase 1: Lexical Analysis - Tokenizer/Lexer

## Overview
Phase 1 implements the lexical analysis stage of the compiler frontend. The tokenizer converts raw source code (arithmetic expressions) into a stream of tokens that can be processed by the parser.

## Goal
Convert arithmetic expressions into structured tokens:
```
Input:  "3 + 4 * (2 - 1)"
Output: NUMBER(3) PLUS NUMBER(4) STAR LPAREN NUMBER(2) MINUS NUMBER(1) RPAREN
```

## Implementation

### Files Created
- **`token.h`** - Defines `TokenType` enum and `Token` struct
- **`lexer.h`** - Declares the `Lexer` class interface
- **`lexer.cpp`** - Implements tokenization logic

### Token Types
```cpp
enum class TokenType {
    NUMBER,   // Integer literals
    PLUS,     // +
    MINUS,    // -
    STAR,     // *
    SLASH,    // /
    LPAREN,   // (
    RPAREN,   // )
    END,      // End of input
    INVALID   // Error token
};
```

### Lexer Class
**Key Methods:**
- `nextToken()` - Returns the next token from input
- `tokenize()` - Returns all tokens as a vector
- `advance()` - Moves to next character
- `skipWhitespace()` - Ignores spaces, tabs, newlines
- `readNumber()` - Reads multi-digit integers

**Features:**
- Single-pass scanning
- Automatic whitespace handling
- Multi-digit number support
- Error detection for invalid characters

## Testing
```bash
g++ -std=c++11 -o lexer_test main.cpp lexer.cpp
./lexer_test
```

**Test Expression:** `"3 + 4 * (2 - 1)"`

**Expected Output:**
```
NUMBER(3) PLUS NUMBER(4) STAR LPAREN NUMBER(2) MINUS NUMBER(1) RPAREN
```

## Status
✅ **Complete** - All basic tokenization features implemented and tested

## Next Steps
- Phase 2: Parser (Syntax Analysis)
- Phase 3: AST Generation
- Phase 4: Evaluator
