#include <iostream>
#include <string>
#include <iomanip>
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

void testEvaluate(const std::string& expression) {
    std::cout << "Input: \"" << expression << "\"\n";
    
    try {
        // Step 1: Tokenize
        Lexer lexer(expression);
        std::vector<Token> tokens = lexer.tokenize();
        
        // Step 2: Parse
        Parser parser(tokens);
        auto ast = parser.parse();
        
        // Step 3: Display AST
        std::cout << "AST:    " << ast->toString() << "\n";
        
        // Step 4: Evaluate
        double result = Evaluator::evaluate(ast.get());
        
        // Step 5: Display result
        std::cout << "Result: ";
        if (result == static_cast<int>(result)) {
            std::cout << static_cast<int>(result);
        } else {
            std::cout << std::fixed << std::setprecision(2) << result;
        }
        std::cout << "\n";
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    
    std::cout << "\n";
}

int main() {
    std::cout << "=== EVALUATOR TESTS ===\n\n";
    
    // Basic operations
    testEvaluate("3 + 4");
    testEvaluate("10 - 3");
    testEvaluate("5 * 6");
    testEvaluate("20 / 4");
    
    // Precedence
    testEvaluate("3 + 4 * 2");
    testEvaluate("10 - 2 * 3");
    testEvaluate("2 * 3 + 4");
    
    // Parentheses
    testEvaluate("(3 + 4) * 2");
    testEvaluate("10 / (2 + 3)");
    
    // Left associativity
    testEvaluate("10 - 3 - 2");
    testEvaluate("20 / 4 / 2");
    
    // Complex expressions
    testEvaluate("3 + 4 * 2 - 1");
    testEvaluate("((3 + 4) * 2) - 1");
    testEvaluate("2 * (3 + 4) - 5");
    
    // Floating point
    testEvaluate("3.14 + 2.86");
    testEvaluate("10.5 / 2");
    testEvaluate("3.5 * 2.5");
    
    // Edge cases
    testEvaluate("0 + 0");
    testEvaluate("1 * 1");
    testEvaluate("5 - 5");
    
    // Error: Division by zero
    testEvaluate("10 / 0");
    testEvaluate("5 / (3 - 3)");
    
    return 0;
}
