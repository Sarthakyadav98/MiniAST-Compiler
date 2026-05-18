#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

enum class TokenType {
    NUMBER,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    LPAREN,
    RPAREN,
    END,
    INVALID
};

struct Token {
    TokenType type;
    string value;
    
    Token(TokenType t, const string& v = "") : type(t), value(v) {}
};

#endif // TOKEN_H
