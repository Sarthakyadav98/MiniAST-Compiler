#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <string>
#include <vector>
using namespace std;

class Lexer {
private:
    string input;
    size_t pos;
    char currentChar;
    
    void advance();
    void skipWhitespace();
    string readNumber();
    char peek() const;
    
public:
    Lexer(const string& text);
    Token nextToken();
    vector<Token> tokenize();
};

#endif // LEXER_H
