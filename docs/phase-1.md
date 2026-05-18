# Phase 1: Lexical Analysis - Tokenizer/Lexer

## Overview
Phase 1 implements the lexical analysis stage of the compiler frontend. The tokenizer converts raw source code (arithmetic expressions) into a stream of tokens that can be processed by the parser.

## Goal
Convert arithmetic expressions into structured tokens:
```
Input:  "3 + 4 * (2 - 1)"
Output: NUMBER(3) PLUS NUMBER(4) MULTIPLY LEFT_PAREN NUMBER(2) MINUS NUMBER(1) RIGHT_PAREN END_OF_FILE
```

## Implementation

### Files Created
- **`token.h`** - Defines `TokenType` enum and `Token` struct
- **`lexer.h`** - Declares the `Lexer` class interface
- **`lexer.cpp`** - Implements tokenization logic
- **`test_cases.txt`** - Comprehensive test cases
- **`main.cpp`** - Test driver that reads from test_cases.txt

### Token Types
```cpp
enum class TokenType {
    // Literals
    NUMBER,

    // Operators
    PLUS,           // +
    MINUS,          // -
    MULTIPLY,       // *
    DIVIDE,         // /

    // Parentheses
    LEFT_PAREN,     // (
    RIGHT_PAREN,    // )

    // Special tokens
    END_OF_FILE,    // End of input
    INVALID         // Error token
};
```

### Token Structure
```cpp
struct Token {
    TokenType type;
    std::string lexeme;  // Raw text from source (proper compiler terminology)
    
    Token(TokenType t, const std::string& lex = "") : type(t), lexeme(lex) {}
};
```

### Lexer Class
**Key Methods:**
- `nextToken()` - Returns the next token from input
- `tokenize()` - Returns all tokens as a vector
- `advance()` - Moves to next character
- `skipWhitespace()` - Ignores spaces, tabs, newlines
- `readNumber()` - Reads integers and floating-point numbers
- `peek()` - Lookahead to next character without consuming
- `isValidNumber()` - Validates number format (single decimal point)

**Features:**
- Single-pass scanning
- Automatic whitespace handling
- Multi-digit integer support
- **Floating-point number support** (e.g., `3.14`, `.25`)
- Leading decimal normalization (`.02` → `0.02`)
- Invalid number detection (e.g., `3.1.4` → `INVALID`)
- Error detection for invalid characters
- Proper compiler terminology (`lexeme` instead of `value`)
- **No `using namespace std;` in headers** (C++ best practice)

## Testing
```bash
g++ -std=c++11 -o lexer_test main.cpp lexer.cpp
./lexer_test
```

### Comprehensive Test Cases
The lexer passes all 10 critical test cases:

1. **Basic Expression**: `3 + 4 * 2` → `NUMBER PLUS NUMBER MULTIPLY NUMBER`
2. **Parentheses**: `(3 + 2) * 5` → Correct tokenization
3. **Floating Point**: `3.14 + 2.7` → `NUMBER(3.14) PLUS NUMBER(2.7)`
4. **Leading Decimal**: `.25 + .5` → `NUMBER(0.25) PLUS NUMBER(0.5)`
5. **Invalid Decimal**: `3.1.4` → `INVALID(3.1.4)`
6. **Multiple Invalid Decimals**: `3..1..2` → `INVALID(3..1..2)`
7. **Invalid Character**: `3 + @` → `NUMBER PLUS INVALID(@)`
8. **Empty Input**: `""` → `END_OF_FILE` only
9. **Whitespace Handling**: `3    +    4` → Correct tokenization
10. **Consecutive Operators**: `3 ++ 4` → `PLUS PLUS` (lexer tokenizes, parser handles syntax error)

## Key Design Decisions

### Compiler Stage Separation
The lexer only tokenizes - it does NOT validate syntax. For example:
- `3 ++ 4` tokenizes as `NUMBER PLUS PLUS NUMBER`
- The parser (Phase 2) will detect this as a syntax error
- This is proper compiler design: **lexical analysis ≠ syntax analysis**

### Professional C++ Practices
- ✅ Fully qualified `std::` in headers (no `using namespace std;`)
- ✅ Proper compiler terminology (`lexeme` for raw token text)
- ✅ Semantic token names (`MULTIPLY` not `STAR`, `LEFT_PAREN` not `LPAREN`)
- ✅ Lookahead with `peek()` for multi-character token support
- ✅ Comprehensive error handling with `INVALID` token type

## Status
✅ **Complete** - Production-ready lexer with comprehensive test coverage

## Next Steps
- Phase 2: Recursive Descent Parser (Syntax Analysis)
- Phase 3: AST Generation
- Phase 4: Evaluator
