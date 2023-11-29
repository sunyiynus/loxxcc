
#include "gtest/gtest.h"
#include "Utility.h"
#include "config.h"
#include "format.h"
#include "expression.h"

using namespace std;


TEST(ExpressionClass_test, testcase_init_001)
{
    auto literalA1 = std::make_shared<LiteralExpr>();
    literalA1->literal = Token("10", "10", 0, TokenType::NUMBER);
    auto literalA2 = std::make_shared<LiteralExpr>();
    literalA2->literal = Token("11", "11", 0, TokenType::NUMBER);
    auto binaryA2 = std::make_shared<BinaryExpr>();
    binaryA2->op =Token("+", "+", 0, TokenType::PLUS);
    binaryA2->lOperand = literalA1;
    binaryA2->rOperand = literalA2;

}