#include <iostream>
#include "lexer.h"

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::STAR: return "STAR";
        case TokenType::SLASH: return "SLASH";
        case TokenType::LPAREN: return "LPAREN";
        case TokenType::RPAREN: return "RPAREN";
        case TokenType::END: return "END";
        case TokenType::INVALID: return "INVALID";
        default: return "UNKNOWN";
    }
}

int main() {
    std::string expression = "3 + 4 * (2 - 1)";
    
    std::cout << "Input: " << expression << "\n\n";
    std::cout << "Tokens:\n";
    
    Lexer lexer(expression);
    std::vector<Token> tokens = lexer.tokenize();
    
    for (const auto& token : tokens) {
        if (token.type == TokenType::NUMBER) {
            std::cout << tokenTypeToString(token.type) << "(" << token.value << ") ";
        } else if (token.type != TokenType::END) {
            std::cout << tokenTypeToString(token.type) << " ";
        }
    }
    
    std::cout << "\n";
    
    return 0;
}
