#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

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
    string value;
    
    Token(TokenType t, const string& v = "") : type(t), value(v) {}
};

#endif // TOKEN_H
