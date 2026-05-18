#ifndef AST_H
#define AST_H

#include <string>
#include <memory>
#include <sstream>
#include <iomanip>

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
        std::ostringstream oss;
        
        // Check if it's an integer value
        if (value == static_cast<int>(value)) {
            oss << static_cast<int>(value);
        } else {
            // Format with minimal decimal places
            oss << std::fixed << std::setprecision(2) << value;
            std::string result = oss.str();
            
            // Remove trailing zeros after decimal point
            size_t decimal_pos = result.find('.');
            if (decimal_pos != std::string::npos) {
                size_t last_nonzero = result.find_last_not_of('0');
                if (last_nonzero > decimal_pos) {
                    result = result.substr(0, last_nonzero + 1);
                }
                // Remove decimal point if no digits after it
                if (result.back() == '.') {
                    result.pop_back();
                }
            }
            return result;
        }
        
        return oss.str();
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
