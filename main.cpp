#include <iostream>
#include <fstream>
#include <string>
#include "lexer.h"

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

void testExpression(const std::string& expression, int testNum) {
    std::cout << "Test " << testNum << ": ";
    if (expression.empty()) {
        std::cout << "\"\" (empty string)\n";
    } else {
        std::cout << "\"" << expression << "\"\n";
    }
    
    std::cout << "Tokens: ";
    
    Lexer lexer(expression);
    std::vector<Token> tokens = lexer.tokenize();
    
    for (const auto& token : tokens) {
        if (token.type == TokenType::NUMBER) {
            std::cout << tokenTypeToString(token.type) << "(" << token.lexeme << ") ";
        } else if (token.type == TokenType::INVALID) {
            std::cout << tokenTypeToString(token.type) << "(" << token.lexeme << ") ";
        } else {
            std::cout << tokenTypeToString(token.type) << " ";
        }
    }
    
    std::cout << "\n\n";
}

int main() {
    std::ifstream inputFile("test_cases.txt");
    
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open test_cases.txt\n";
        return 1;
    }
    
    std::string line;
    int testNum = 1;
    
    while (std::getline(inputFile, line)) {
        testExpression(line, testNum);
        testNum++;
    }
    
    inputFile.close();
    
    return 0;
}
