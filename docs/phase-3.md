# Phase 3: Evaluator (Interpreter)

**FINAL PHASE - INTERPRETER-STYLE EXECUTION**

---

## GOAL

Walk the Abstract Syntax Tree (AST) and compute the final result through recursive evaluation.

This is **interpreter-style execution** - a key compiler concept where the AST is directly executed rather than compiled to machine code.

---

## EVALUATION ALGORITHM

Elegant recursive algorithm:

```
evaluate(node):
    if node is NumberNode:
        return node.value
    
    if node is BinaryOpNode:
        leftValue = evaluate(node.left)   // Recursion!
        rightValue = evaluate(node.right) // Recursion!
        return apply(node.op, leftValue, rightValue)
```

### WHY THIS IS ELEGANT

- **Post-order traversal**: Evaluate children before parent
- **Natural recursion**: Mirrors the recursive structure of the AST
- **Operator precedence**: Already handled by AST structure
- **No explicit stack needed**: Call stack handles it automatically

---

## IMPLEMENTATION

### Files Created

- **`evaluator.h`** - Evaluator class declaration
- **`evaluator.cpp`** - Recursive evaluation implementation

### Evaluator Structure

```cpp
class Evaluator {
public:
    static double evaluate(const ASTNode* node);
    
private:
    static double evaluateNumber(const NumberNode* node);
    static double evaluateBinaryOp(const BinaryOpNode* node);
};
```

### Key Methods

1. **`evaluate(node)`**
   - Main entry point
   - Uses dynamic_cast to determine node type
   - Dispatches to appropriate handler

2. **`evaluateNumber(node)`**
   - Base case: returns the number value
   - No recursion needed

3. **`evaluateBinaryOp(node)`**
   - Recursive case
   - Evaluates left subtree (recursion!)
   - Evaluates right subtree (recursion!)
   - Applies operator to results

---

## EXAMPLE EVALUATION

**Input**: `3 + 4 * 2`

**AST**:
```
       +
      / \
     3   *
        / \
       4   2
```

**Evaluation Flow**:
1. `evaluate(+)` called
2. Evaluate left child: `evaluate(3)` → returns `3`
3. Evaluate right child: `evaluate(*)` 
   - Evaluate left: `evaluate(4)` → returns `4`
   - Evaluate right: `evaluate(2)` → returns `2`
   - Apply `*`: `4 * 2` → returns `8`
4. Apply `+`: `3 + 8` → returns `11`

**Result**: `11` ✓

---

## OPERATOR IMPLEMENTATION

```cpp
double Evaluator::evaluateBinaryOp(const BinaryOpNode* node) {
    double leftValue = evaluate(node->left.get());
    double rightValue = evaluate(node->right.get());
    
    if (node->op == "+") return leftValue + rightValue;
    if (node->op == "-") return leftValue - rightValue;
    if (node->op == "*") return leftValue * rightValue;
    if (node->op == "/") {
        if (rightValue == 0.0) {
            throw std::runtime_error("Runtime error: Division by zero");
        }
        return leftValue / rightValue;
    }
    
    throw std::runtime_error("Unknown operator");
}
```

---

## ERROR HANDLING

### Runtime Errors

The evaluator detects runtime errors that can't be caught during parsing:

#### Division by Zero
```
Input:  "10 / 0"
AST:    (10 / 0)
Error:  Runtime error: Division by zero
```

#### Expression Evaluation
```
Input:  "5 / (3 - 3)"
AST:    (5 / (3 - 3))
Error:  Runtime error: Division by zero
```

The evaluator computes `(3 - 3) = 0` first, then detects division by zero.

---

## COMPLETE PIPELINE

The full compiler pipeline:

```
Source Code
    ↓
[LEXER] → Tokens
    ↓
[PARSER] → AST
    ↓
[EVALUATOR] → Result
```

### Example: `3 + 4 * 2`

**Stage 1 - Lexer**:
```
Tokens: NUMBER(3) PLUS NUMBER(4) MULTIPLY NUMBER(2)
```

**Stage 2 - Parser**:
```
AST: (3 + (4 * 2))
```

**Stage 3 - Evaluator**:
```
Result: 11
```

---

## TEST RESULTS

All test cases pass successfully:

### ✅ Basic Operations
- `3 + 4` → `7`
- `10 - 3` → `7`
- `5 * 6` → `30`
- `20 / 4` → `5`

### ✅ Precedence
- `3 + 4 * 2` → `11` (multiplication first)
- `10 - 2 * 3` → `4`
- `2 * 3 + 4` → `10`

### ✅ Parentheses
- `(3 + 4) * 2` → `14` (override precedence)
- `10 / (2 + 3)` → `2`

### ✅ Left Associativity
- `10 - 3 - 2` → `5` (left-to-right: `(10 - 3) - 2`)
- `20 / 4 / 2` → `2.50` (left-to-right: `(20 / 4) / 2`)

### ✅ Complex Expressions
- `3 + 4 * 2 - 1` → `10`
- `((3 + 4) * 2) - 1` → `13`
- `2 * (3 + 4) - 5` → `9`

### ✅ Floating Point
- `3.14 + 2.86` → `6`
- `10.5 / 2` → `5.25`
- `3.5 * 2.5` → `8.75`

### ✅ Edge Cases
- `0 + 0` → `0`
- `1 * 1` → `1`
- `5 - 5` → `0`

### ✅ Runtime Errors
- `10 / 0` → `Runtime error: Division by zero`
- `5 / (3 - 3)` → `Runtime error: Division by zero`

---

## KEY CONCEPTS

### Interpreter vs Compiler

**Interpreter (What We Built)**:
- Directly executes the AST
- No machine code generation
- Immediate results
- Easier to implement
- Good for scripting languages

**Compiler (Alternative)**:
- Translates AST to machine code
- Separate compilation and execution phases
- Faster execution after compilation
- More complex to implement
- Good for system languages

### Post-Order Traversal

The evaluator uses **post-order traversal**:
1. Visit left subtree
2. Visit right subtree
3. Process current node

This ensures operands are evaluated before operators - exactly what we need for arithmetic!

### Call Stack as Execution Stack

The recursive evaluation naturally uses the call stack:
- Each recursive call pushes a frame
- Intermediate results stored in local variables
- Automatic cleanup when returning

This is why we don't need an explicit evaluation stack!

---

## COMPILATION & EXECUTION

### Build
```bash
g++ -std=c++11 -o compiler main.cpp lexer.cpp parser.cpp evaluator.cpp
```

### Run
```bash
./compiler
```

Reads expressions from `test_cases.txt` and outputs:
- Input expression
- Token stream
- AST representation
- Final result

---

## PROFESSIONAL FEATURES

### 1. Smart Result Formatting
- Integers display without decimals: `11` not `11.00`
- Floats display with minimal precision: `5.25` not `5.250000`

### 2. Comprehensive Error Handling
- Division by zero detection
- Unknown operator detection
- Clear error messages

### 3. Type Safety
- Uses `dynamic_cast` for safe type checking
- Proper error handling for unknown node types

### 4. Clean Architecture
- Static methods (no state needed)
- Separation of concerns (each node type has its handler)
- Easy to extend with new operators

---

## IMPLEMENTATION CHECKLIST

- [x] Create `evaluator.h` with Evaluator class
- [x] Create `evaluator.cpp` with recursive evaluation
- [x] Implement `evaluate()` dispatcher
- [x] Implement `evaluateNumber()` for base case
- [x] Implement `evaluateBinaryOp()` for recursive case
- [x] Add division by zero detection
- [x] Test with all Phase 1 and Phase 2 test cases
- [x] Verify precedence: `3 + 4 * 2` → `11` ✓
- [x] Verify associativity: `10 - 3 - 2` → `5` ✓
- [x] Verify parentheses: `(3 + 4) * 2` → `14` ✓
- [x] Verify floating point: `3.5 * 2.5` → `8.75` ✓
- [x] Verify error handling: `10 / 0` → error ✓

---

## STATUS
✅ **COMPLETE** - Full working interpreter for arithmetic expressions

---

## INTERVIEW DISCUSSION POINTS

1. **Interpreter vs Compiler**: Explain the difference and trade-offs
2. **Recursion**: How the evaluator mirrors AST structure
3. **Post-order traversal**: Why it's perfect for expression evaluation
4. **Call stack usage**: How recursion eliminates need for explicit stack
5. **Error handling**: Runtime errors vs compile-time errors
6. **Extensibility**: How to add new operators or functions
7. **Optimization**: Potential improvements (constant folding, etc.)

---

## PROJECT COMPLETE! 🎉

You now have a fully functional arithmetic expression compiler with:
- ✅ Lexical analysis (tokenization)
- ✅ Syntax analysis (parsing with precedence)
- ✅ Semantic analysis (AST generation)
- ✅ Interpretation (evaluation)

This demonstrates core compiler concepts and is an excellent portfolio project!
