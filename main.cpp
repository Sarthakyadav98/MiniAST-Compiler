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
    std::string expression = "3 + 4 * ($ - 1)";
    
    std::cout << "Input: " << expression << "\n\n";
    std::cout << "Tokens:\n";
    
    Lexer lexer(expression);
    std::vector<Token> tokens = lexer.tokenize();
    
    for (const auto& token : tokens) {
        if (token.type == TokenType::NUMBER) {
            std::cout << tokenTypeToString(token.type) << "(" << token.value << ") ";
        } else if (token.type != TokenType::END_OF_FILE) {
            std::cout << tokenTypeToString(token.type) << " ";
        }
    }
    
    std::cout << "\n";
    
    return 0;
}
