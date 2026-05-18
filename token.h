#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    // Literals
    NUMBER,

    // Operators
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,

    // Parentheses
    LEFT_PAREN,
    RIGHT_PAREN,

    // Special tokens
    END_OF_FILE,
    INVALID
};





struct Token {
    TokenType type;
    std::string lexeme;
    
    Token(TokenType t, const std::string& lex = "") : type(t), lexeme(lex) {}
};

#endif // TOKEN_H
