#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "ast.h"
#include <vector>
#include <memory>
#include <stdexcept>

class Parser {
private:
    std::vector<Token> tokens;
    size_t pos;
    Token currentToken;
    
    void advance();
    void expect(TokenType type, const std::string& message);
    
    std::unique_ptr<ASTNode> parseExpression();
    std::unique_ptr<ASTNode> parseTerm();
    std::unique_ptr<ASTNode> parseFactor();
    
public:
    explicit Parser(const std::vector<Token>& toks);
    std::unique_ptr<ASTNode> parse();
};

#endif // PARSER_H
