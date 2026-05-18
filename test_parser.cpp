#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"

void testParse(const std::string& expression) {
    std::cout << "Input: \"" << expression << "\"\n";
    
    try {
        // Tokenize
        Lexer lexer(expression);
        std::vector<Token> tokens = lexer.tokenize();
        
        // Parse
        Parser parser(tokens);
        auto ast = parser.parse();
        
        // Print AST
        std::cout << "AST: " << ast->toString() << "\n";
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    
    std::cout << "\n";
}

int main() {
    std::cout << "=== PARSER TESTS ===\n\n";
    
    // Test 1: Basic precedence
    testParse("3 + 4 * 2");
    
    // Test 2: Parentheses override precedence
    testParse("(3 + 4) * 2");
    
    // Test 3: Left associativity
    testParse("8 - 4 - 2");
    
    // Test 4: Complex expression
    testParse("3 + 4 * 2 - 1");
    
    // Test 5: Nested parentheses
    testParse("((3 + 4) * 2) - 1");
    
    // Test 6: Division
    testParse("10 / 2 + 3");
    
    // Test 7: Floating point
    testParse("3.14 + 2.5 * 2");
    
    // Test 8: Error - consecutive operators
    testParse("3 + + 4");
    
    // Test 9: Error - missing operand
    testParse("3 +");
    
    // Test 10: Error - unmatched parenthesis
    testParse("(3 + 4");
    
    return 0;
}
