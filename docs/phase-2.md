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

## PARSER STRUCTURE

Classic recursive descent structure:

```cpp
class Parser {
private:
    std::vector<Token> tokens;
    size_t pos;
    Token currentToken;
    
    void advance();
    void expect(TokenType type);
    
    ASTNode* parseExpression();  // Handles + and -
    ASTNode* parseTerm();         // Handles * and /
    ASTNode* parseFactor();       // Handles numbers and ()
    
public:
    Parser(const std::vector<Token>& tokens);
    ASTNode* parse();
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

Parser should detect:
- **Unexpected tokens**: `3 + + 4` (consecutive operators)
- **Missing operands**: `3 +` (incomplete expression)
- **Unmatched parentheses**: `(3 + 4` (missing closing paren)
- **Invalid factor**: `+ 3` (operator where number expected)

Use `expect()` method to validate token types and throw descriptive errors.

---

## IMPLEMENTATION CHECKLIST

- [ ] Create `ast.h` with AST node structures
- [ ] Create `parser.h` with Parser class declaration
- [ ] Create `parser.cpp` with recursive descent implementation
- [ ] Implement `parseExpression()` for `+` and `-`
- [ ] Implement `parseTerm()` for `*` and `/`
- [ ] Implement `parseFactor()` for numbers and `()`
- [ ] Add error handling with descriptive messages
- [ ] Test with expressions from Phase 1 test cases
- [ ] Verify precedence: `3 + 4 * 2` should parse as `3 + (4 * 2)`
- [ ] Verify associativity: `8 - 4 - 2` should parse as `(8 - 4) - 2`
- [ ] Verify parentheses: `(3 + 4) * 2` should parse correctly

---

## NEXT STEPS

After parser is complete:
- **Phase 3**: AST Traversal and Visualization
- **Phase 4**: Evaluator (interpret the AST)

---

## STATUS
⏳ **In Progress** - Ready to implement
