#include <iostream>
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

int main() {
    // Test 1: Basic integer expression
    std::string expression = "3 + 4 * (2 - 1)";
    
    std::cout << "Input: " << expression << "\n\n";
    std::cout << "Tokens:\n";
    
    Lexer lexer(expression);
    std::vector<Token> tokens = lexer.tokenize();
    
    for (const auto& token : tokens) {
        if (token.type == TokenType::NUMBER) {
            std::cout << tokenTypeToString(token.type) << "(" << token.value << ") ";
        } else if (token.type == TokenType::INVALID) {
            std::cout << tokenTypeToString(token.type) << "(" << token.value << ") ";
        } else if (token.type != TokenType::END_OF_FILE) {
            std::cout << tokenTypeToString(token.type) << " ";
        }
    }
    
    std::cout << "\n\n";
    
    // Test 2: Floating point numbers
    std::string floatExpr = "3.14 + 2.5 * (10.0 - 1.25)";
    
    std::cout << "Input: " << floatExpr << "\n\n";
    std::cout << "Tokens:\n";
    
    Lexer lexer2(floatExpr);
    std::vector<Token> tokens2 = lexer2.tokenize();
    
    for (const auto& token : tokens2) {
        if (token.type == TokenType::NUMBER) {
            std::cout << tokenTypeToString(token.type) << "(" << token.value << ") ";
        } else if (token.type == TokenType::INVALID) {
            std::cout << tokenTypeToString(token.type) << "(" << token.value << ") ";
        } else if (token.type != TokenType::END_OF_FILE) {
            std::cout << tokenTypeToString(token.type) << " ";
        }
    }
    
    std::cout << "\n\n";
    
    // Test 3: Leading decimal point
    std::string leadingDecimal = ".02 + 4 * (2 - 1)";
    
    std::cout << "Input: " << leadingDecimal << "\n\n";
    std::cout << "Tokens:\n";
    
    Lexer lexer3(leadingDecimal);
    std::vector<Token> tokens3 = lexer3.tokenize();
    
    for (const auto& token : tokens3) {
        if (token.type == TokenType::NUMBER) {
            std::cout << tokenTypeToString(token.type) << "(" << token.value << ") ";
        } else if (token.type == TokenType::INVALID) {
            std::cout << tokenTypeToString(token.type) << "(" << token.value << ") ";
        } else if (token.type != TokenType::END_OF_FILE) {
            std::cout << tokenTypeToString(token.type) << " ";
        }
    }
    
    std::cout << "\n\n";
    
    // Test 4: Multiple decimal points (invalid)
    std::string multiDecimal = "3.00.1 + 4 * (2 - 1)";
    
    std::cout << "Input: " << multiDecimal << "\n\n";
    std::cout << "Tokens:\n";
    
    Lexer lexer4(multiDecimal);
    std::vector<Token> tokens4 = lexer4.tokenize();
    
    for (const auto& token : tokens4) {
        if (token.type == TokenType::NUMBER) {
            std::cout << tokenTypeToString(token.type) << "(" << token.value << ") ";
        } else if (token.type == TokenType::INVALID) {
            std::cout << tokenTypeToString(token.type) << "(" << token.value << ") ";
        } else if (token.type != TokenType::END_OF_FILE) {
            std::cout << tokenTypeToString(token.type) << " ";
        }
    }
    
    std::cout << "\n";
    
    return 0;
}
