#include "parser.h"
#include <sstream>

Parser::Parser(const std::vector<Token>& toks) 
    : tokens(toks), pos(0), currentToken(TokenType::END_OF_FILE, "") {
    if (!tokens.empty()) {
        currentToken = tokens[0];
    }
}

void Parser::advance() {
    if (pos < tokens.size() - 1) {
        pos++;
        currentToken = tokens[pos];
    }
}

void Parser::expect(TokenType type, const std::string& message) {
    if (currentToken.type != type) {
        throw std::runtime_error("Parse error: " + message + 
                                 " (got " + currentToken.lexeme + ")");
    }
    advance();
}

std::unique_ptr<ASTNode> Parser::parse() {
    if (tokens.empty() || tokens[0].type == TokenType::END_OF_FILE) {
        throw std::runtime_error("Parse error: Empty input");
    }
    
    auto result = parseExpression();
    
    if (currentToken.type != TokenType::END_OF_FILE) {
        throw std::runtime_error("Parse error: Unexpected token after expression: " + 
                                 currentToken.lexeme);
    }
    
    return result;
}

// Expr → Term ((PLUS | MINUS) Term)*
std::unique_ptr<ASTNode> Parser::parseExpression() {
    auto left = parseTerm();
    
    while (currentToken.type == TokenType::PLUS || 
           currentToken.type == TokenType::MINUS) {
        std::string op = currentToken.lexeme;
        advance();
        auto right = parseTerm();
        left = std::unique_ptr<ASTNode>(new BinaryOpNode(op, std::move(left), std::move(right)));
    }
    
    return left;
}

// Term → Factor ((MULTIPLY | DIVIDE) Factor)*
std::unique_ptr<ASTNode> Parser::parseTerm() {
    auto left = parseFactor();
    
    while (currentToken.type == TokenType::MULTIPLY || 
           currentToken.type == TokenType::DIVIDE) {
        std::string op = currentToken.lexeme;
        advance();
        auto right = parseFactor();
        left = std::unique_ptr<ASTNode>(new BinaryOpNode(op, std::move(left), std::move(right)));
    }
    
    return left;
}

// Factor → NUMBER | LEFT_PAREN Expr RIGHT_PAREN
std::unique_ptr<ASTNode> Parser::parseFactor() {
    // Handle numbers
    if (currentToken.type == TokenType::NUMBER) {
        double value = std::stod(currentToken.lexeme);
        advance();
        return std::unique_ptr<ASTNode>(new NumberNode(value));
    }
    
    // Handle parentheses
    if (currentToken.type == TokenType::LEFT_PAREN) {
        advance();  // consume '('
        auto expr = parseExpression();
        expect(TokenType::RIGHT_PAREN, "Expected closing parenthesis");
        return expr;
    }
    
    // Error: unexpected token
    throw std::runtime_error("Parse error: Expected number or '(', got " + 
                             currentToken.lexeme);
}
