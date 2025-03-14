#ifndef AST_H
#define AST_H

#include <string>
#include <memory>

// Base class for all AST nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual std::string toString() const = 0;
};

// Number literal node
class NumberNode : public ASTNode {
public:
    double value;
    
    explicit NumberNode(double val) : value(val) {}
    
    std::string toString() const override {
        return std::to_string(value);
    }
};

// Binary operation node (for +, -, *, /)
class BinaryOpNode : public ASTNode {
public:
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    
    BinaryOpNode(const std::string& operation, 
                 std::unique_ptr<ASTNode> l, 
                 std::unique_ptr<ASTNode> r)
        : op(operation), left(std::move(l)), right(std::move(r)) {}
    
    std::string toString() const override {
        return "(" + left->toString() + " " + op + " " + right->toString() + ")";
    }
};

#endif // AST_H
