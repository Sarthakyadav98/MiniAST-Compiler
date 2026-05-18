#include "lexer.h"
#include <cctype>
using namespace std;

Lexer::Lexer(const string& text) : input(text), pos(0) {
    currentChar = input.empty() ? '\0' : input[0];
}

void Lexer::advance() {
    pos++;
    if (pos >= input.length()) {
        currentChar = '\0';
    } else {
        currentChar = input[pos];
    }
}

void Lexer::skipWhitespace() {
    while (currentChar != '\0' && isspace(currentChar)) {
        advance();
    }
}

string Lexer::readNumber() {
    string result;
    while (currentChar != '\0' && isdigit(currentChar)) {
        result += currentChar;
        advance();
    }
    return result;
}

Token Lexer::nextToken() {
    while (currentChar != '\0') {
        if (isspace(currentChar)) {
            skipWhitespace();
            continue;
        }
        
        if (isdigit(currentChar)) {
            return Token(TokenType::NUMBER, readNumber());
        }
        
        if (currentChar == '+') {
            advance();
            return Token(TokenType::PLUS, "+");
        }
        
        if (currentChar == '-') {
            advance();
            return Token(TokenType::MINUS, "-");
        }
        
        if (currentChar == '*') {
            advance();
            return Token(TokenType::MULTIPLY, "*");
        }
        
        if (currentChar == '/') {
            advance();
            return Token(TokenType::DIVIDE, "/");
        }
        
        if (currentChar == '(') {
            advance();
            return Token(TokenType::LEFT_PAREN, "(");
        }
        
        if (currentChar == ')') {
            advance();
            return Token(TokenType::RIGHT_PAREN, ")");
        }
        
        // Invalid character
        advance();
        return Token(TokenType::INVALID, string(1, currentChar));
    }
    
    return Token(TokenType::END_OF_FILE, "");
}

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;
    Token token = nextToken();
    
    while (token.type != TokenType::END_OF_FILE) {
        tokens.push_back(token);
        token = nextToken();
    }
    
    tokens.push_back(token); // Add END_OF_FILE token
    return tokens;
}
