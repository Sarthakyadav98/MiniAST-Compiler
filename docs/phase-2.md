# Phase 2: Recursive Descent Parser

**MOST IMPORTANT PHASE**

---

## GOAL

Convert token stream into **Abstract Syntax Tree (AST)** while handling:
- **Operator precedence** (`*` and `/` before `+` and `-`)
- **Associativity** (left-to-right for same precedence)
- **Parentheses** (override precedence)

---

## GRAMMAR

Simple, elegant grammar that naturally encodes precedence:

```
Expr   → Term ((PLUS | MINUS) Term)*
Term   → Factor ((MULTIPLY | DIVIDE) Factor)*
Factor → NUMBER | LEFT_PAREN Expr RIGHT_PAREN
```

### WHY THIS GRAMMAR IS IMPORTANT

It **naturally handles precedence**:
- `Expr` handles lowest precedence (`+`, `-`)
- `Term` handles higher precedence (`*`, `/`)
- `Factor` handles highest precedence (numbers, parentheses)

**Example**: `3 + 4 * 2`
- Parser calls `parseExpression()`
- Sees `3` as a `Term`, which is a `Factor` (number)
- Sees `+`, continues in `Expr`
- Sees `4 * 2` as another `Term`
  - Inside `Term`, `4` is a `Factor`
  - Sees `*`, continues in `Term`
  - Sees `2` as another `Factor`
- Result: `+` at root, `*` as child → **correct precedence**

Very elegant! No precedence table needed.

---

## IMPLEMENTATION

### Files Created

- **`ast.h`** - AST node structures (NumberNode, BinaryOpNode)
- **`parser.h`** - Parser class declaration
- **`parser.cpp`** - Recursive descent implementation
- **`test_parser.cpp`** - Comprehensive parser tests

### AST Structure

```cpp
// Base class for all AST nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual std::string toString() const = 0;
};

// Number literal node
class NumberNode : public ASTNode {
public:
    double value;
    std::string toString() const override;  // Smart formatting
};

// Binary operation node (for +, -, *, /)
class BinaryOpNode : public ASTNode {
public:
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    std::string toString() const override;
};
```

### Parser Structure

```cpp
class Parser {
private:
    std::vector<Token> tokens;
    size_t pos;
    Token currentToken;
    
    void advance();
    void expect(TokenType type, const std::string& message);
    
    std::unique_ptr<ASTNode> parseExpression();  // Handles + and -
    std::unique_ptr<ASTNode> parseTerm();         // Handles * and /
    std::unique_ptr<ASTNode> parseFactor();       // Handles numbers and ()
    
public:
    explicit Parser(const std::vector<Token>& tokens);
    std::unique_ptr<ASTNode> parse();
};
```

### PARSER METHODS

1. **`parseExpression()`**
   - Handles addition and subtraction
   - Calls `parseTerm()` for operands
   - Left-associative: `3 - 2 - 1` → `(3 - 2) - 1`

2. **`parseTerm()`**
   - Handles multiplication and division
   - Calls `parseFactor()` for operands
   - Left-associative: `8 / 4 / 2` → `(8 / 4) / 2`

3. **`parseFactor()`**
   - Handles numbers and parenthesized expressions
   - Base case of recursion
   - Calls `parseExpression()` for parentheses (recursion!)

---

## EXAMPLE PARSE

**Input**: `3 + 4 * 2`

**Token Stream**: `NUMBER(3) PLUS NUMBER(4) MULTIPLY NUMBER(2) END_OF_FILE`

**Parse Tree**:
```
       +
      / \
     3   *
        / \
       4   2
```

**AST Output**: `(3 + (4 * 2))`

**Execution Flow**:
1. `parseExpression()` called
2. Calls `parseTerm()` → returns `3`
3. Sees `PLUS`, continues
4. Calls `parseTerm()` again
   - Inside `parseTerm()`: sees `4`
   - Sees `MULTIPLY`, continues
   - Calls `parseFactor()` → returns `2`
   - Returns `4 * 2` subtree
5. Returns `3 + (4 * 2)` tree

---

## ERROR HANDLING

### Clean Stage Separation

The parser implements **excellent compiler architecture** with clean error separation:

#### Lexer Errors (Caught Early)
Before parsing begins, all tokens are validated:
- **Invalid characters**: `3 + @` → `Lexer error: Invalid token '@'`
- **Malformed numbers**: `3.1.4` → `Lexer error: Invalid token '3.1.4'`

#### Parser Errors (Syntax Issues)
- **Consecutive operators**: `3 + + 4` → `Parse error: Expected number or '(', got +`
- **Missing operands**: `3 +` → `Parse error: Expected number or '(', got EOF`
- **Unmatched parentheses**: `(3 + 4` → `Parse error: Expected closing parenthesis (got EOF)`

### Professional Error Messages

Helper function `tokenDisplay()` provides clean error output:
- EOF tokens display as `"EOF"` instead of empty string
- All error messages are clear and actionable

---

## KEY FEATURES IMPLEMENTED

### ✅ Correct Precedence
```
Input: 3 + 4 * 2
AST:   (3 + (4 * 2))
```
Multiplication evaluated before addition.

### ✅ Left Associativity
```
Input: 8 - 4 - 2
AST:   ((8 - 4) - 2)
```
Left-to-right evaluation for same precedence.

### ✅ Parentheses Override
```
Input: (3 + 4) * 2
AST:   ((3 + 4) * 2)
```
Parentheses force addition before multiplication.

### ✅ Nested Parentheses
```
Input: ((3 + 4) * 2) - 1
AST:   (((3 + 4) * 2) - 1)
```
Handles arbitrary nesting depth.

### ✅ Floating Point Support
```
Input: 3.14 + 2.5 * 2
AST:   (3.14 + (2.5 * 2))
```
Works seamlessly with floats from lexer.

### ✅ Clean AST Output
- Integers display without decimals: `3` not `3.000000`
- Floats display with minimal precision: `3.14` not `3.140000`
- Trailing zeros removed: `2.5` not `2.50`

---

## TESTING

### Compilation
```bash
g++ -std=c++11 -o test_parser test_parser.cpp lexer.cpp parser.cpp
./test_parser
```

### Test Results

All 12 test cases pass:

1. ✅ **Basic precedence**: `3 + 4 * 2` → `(3 + (4 * 2))`
2. ✅ **Parentheses override**: `(3 + 4) * 2` → `((3 + 4) * 2)`
3. ✅ **Left associativity**: `8 - 4 - 2` → `((8 - 4) - 2)`
4. ✅ **Complex expression**: `3 + 4 * 2 - 1` → `((3 + (4 * 2)) - 1)`
5. ✅ **Nested parentheses**: `((3 + 4) * 2) - 1` → correct
6. ✅ **Division**: `10 / 2 + 3` → `((10 / 2) + 3)`
7. ✅ **Floating point**: `3.14 + 2.5 * 2` → `(3.14 + (2.5 * 2))`
8. ✅ **Error - consecutive operators**: `3 + + 4` → Parse error
9. ✅ **Error - missing operand**: `3 +` → Parse error with EOF
10. ✅ **Error - unmatched paren**: `(3 + 4` → Parse error with EOF
11. ✅ **Error - invalid character**: `3 + @` → Lexer error
12. ✅ **Error - invalid number**: `3.1.4 + 2` → Lexer error

---

## PROFESSIONAL IMPROVEMENTS

### 1. Smart Number Formatting
Uses `std::ostringstream` with intelligent formatting:
- Detects integers vs floats
- Removes trailing zeros
- Minimal decimal places

### 2. Clean Error Messages
`tokenDisplay()` helper ensures:
- EOF displays as `"EOF"` not empty string
- All tokens have readable representation

### 3. Early Invalid Token Detection
Validates all tokens before parsing:
- Prevents confusing cascading errors
- Clear separation between lexer and parser errors

### 4. C++11 Compatibility
- Uses `new` instead of `std::make_unique` (C++14)
- Proper initialization of all members
- Smart pointer management with `std::unique_ptr`

---

## IMPLEMENTATION CHECKLIST

- [x] Create `ast.h` with AST node structures
- [x] Create `parser.h` with Parser class declaration
- [x] Create `parser.cpp` with recursive descent implementation
- [x] Implement `parseExpression()` for `+` and `-`
- [x] Implement `parseTerm()` for `*` and `/`
- [x] Implement `parseFactor()` for numbers and `()`
- [x] Add error handling with descriptive messages
- [x] Test with expressions from Phase 1 test cases
- [x] Verify precedence: `3 + 4 * 2` → `(3 + (4 * 2))` ✓
- [x] Verify associativity: `8 - 4 - 2` → `((8 - 4) - 2)` ✓
- [x] Verify parentheses: `(3 + 4) * 2` → correct ✓
- [x] Early invalid token detection
- [x] Professional error messages with EOF handling
- [x] Clean AST output formatting

---

## STATUS
✅ **COMPLETE** - Production-ready recursive descent parser

---

## NEXT STEPS

- **Phase 3**: Evaluator (interpret the AST and compute results)
