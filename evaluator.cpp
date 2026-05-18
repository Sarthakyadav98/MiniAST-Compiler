#include "evaluator.h"

double Evaluator::evaluate(const ASTNode* node) {
    // Try to cast to NumberNode
    if (const NumberNode* numNode = dynamic_cast<const NumberNode*>(node)) {
        return evaluateNumber(numNode);
    }
    
    // Try to cast to BinaryOpNode
    if (const BinaryOpNode* binNode = dynamic_cast<const BinaryOpNode*>(node)) {
        return evaluateBinaryOp(binNode);
    }
    
    throw std::runtime_error("Evaluation error: Unknown node type");
}

double Evaluator::evaluateNumber(const NumberNode* node) {
    return node->value;
}

double Evaluator::evaluateBinaryOp(const BinaryOpNode* node) {
    // Recursively evaluate left and right subtrees
    double leftValue = evaluate(node->left.get());
    double rightValue = evaluate(node->right.get());
    
    // Apply operator
    if (node->op == "+") {
        return leftValue + rightValue;
    }
    else if (node->op == "-") {
        return leftValue - rightValue;
    }
    else if (node->op == "*") {
        return leftValue * rightValue;
    }
    else if (node->op == "/") {
        if (rightValue == 0.0) {
            throw std::runtime_error("Runtime error: Division by zero");
        }
        return leftValue / rightValue;
    }
    
    throw std::runtime_error("Evaluation error: Unknown operator '" + node->op + "'");
}
