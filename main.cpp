#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::MULTIPLY: return "MULTIPLY";
        case TokenType::DIVIDE: return "DIVIDE";
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        case TokenType::INVALID: return "INVALID";
        default: return "UNKNOWN";
    }
}

void processExpression(const std::string& expression, int testNum) {
    std::cout << "----------------------------------------\n";
    std::cout << "Test " << testNum << "\n";
    std::cout << "----------------------------------------\n";
    
    if (expression.empty()) {
        std::cout << "Input:  \"\" (empty string)\n";
    } else {
        std::cout << "Input:  \"" << expression << "\"\n";
    }
    
    try {
        // Step 1: Lexical Analysis (Tokenization)
        Lexer lexer(expression);
        std::vector<Token> tokens = lexer.tokenize();
        
        std::cout << "Tokens: ";
        for (const auto& token : tokens) {
            if (token.type == TokenType::NUMBER) {
                std::cout << tokenTypeToString(token.type) << "(" << token.lexeme << ") ";
            } else if (token.type == TokenType::INVALID) {
                std::cout << tokenTypeToString(token.type) << "(" << token.lexeme << ") ";
            } else if (token.type != TokenType::END_OF_FILE) {
                std::cout << tokenTypeToString(token.type) << " ";
            }
        }
        std::cout << "\n";
        
        // Step 2: Syntax Analysis (Parsing)
        Parser parser(tokens);
        auto ast = parser.parse();
        
        std::cout << "AST:    " << ast->toString() << "\n";
        
        // Step 3: Evaluation (Interpretation)
        double result = Evaluator::evaluate(ast.get());
        
        std::cout << "Result: ";
        if (result == static_cast<int>(result)) {
            std::cout << static_cast<int>(result);
        } else {
            std::cout << std::fixed << std::setprecision(2) << result;
        }
        std::cout << "\n";
        
    } catch (const std::exception& e) {
        std::cout << "Error:  " << e.what() << "\n";
    }
    
    std::cout << "\n";
}

int main() {
    std::cout << "\n";
    std::cout << "============================================\n";
    std::cout << "  MINI ARITHMETIC EXPRESSION COMPILER\n";
    std::cout << "  Lexer -> Parser -> Evaluator\n";
    std::cout << "============================================\n";
    std::cout << "\n";
    
    std::ifstream inputFile("test_cases.txt");
    
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open test_cases.txt\n";
        std::cerr << "Please ensure the file exists in the current directory.\n";
        return 1;
    }
    
    std::string line;
    int testNum = 1;
    
    while (std::getline(inputFile, line)) {
        processExpression(line, testNum);
        testNum++;
    }
    
    inputFile.close();
    
    std::cout << "----------------------------------------\n";
    std::cout << "All tests completed!\n";
    std::cout << "----------------------------------------\n";
    
    return 0;
}
