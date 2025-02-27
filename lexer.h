#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <string>
#include <vector>

class Lexer {
private:
    std::string input;
    size_t pos;
    char currentChar;
    
    void advance();
    void skipWhitespace();
    std::string readNumber();
    char peek() const;
    bool isValidNumber(const std::string& num) const;
    
public:
    Lexer(const std::string& text);
    Token nextToken();
    std::vector<Token> tokenize();
};

#endif // LEXER_H
