#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "ast.h"
#include <stdexcept>

class Evaluator {
public:
    static double evaluate(const ASTNode* node);
    
private:
    static double evaluateNumber(const NumberNode* node);
    static double evaluateBinaryOp(const BinaryOpNode* node);
};

#endif // EVALUATOR_H
