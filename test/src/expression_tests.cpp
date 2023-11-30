
#include "gtest/gtest.h"
#include "Utility.h"
#include "config.h"
#include "format.h"
#include "expression.h"
#include "printer.h"

using namespace std;

TEST(PrinterClass_test, testcase_init_001)
{
    auto literalA1 = std::make_shared<LiteralExpr>();
    literalA1->literal = Token("10", "10", 0, TokenType::NUMBER);
    auto literalA2 = std::make_shared<LiteralExpr>();
    literalA2->literal = Token("11", "11", 0, TokenType::NUMBER);
    auto binaryA2 = std::make_shared<BinaryExpr>();
    binaryA2->op = Token("+", "+", 0, TokenType::PLUS);
    binaryA2->lOperand = literalA1;
    binaryA2->rOperand = literalA2;
    ASSERT_TRUE(binaryA2.get() != nullptr);
    ASSERT_TRUE(binaryA2.get()->lOperand.get() != nullptr);
    ASSERT_TRUE(binaryA2.get()->rOperand.get() != nullptr);
    Printer printer;
    auto res = binaryA2->accept(&printer);
    ASSERT_EQ(res->resultStr, std::string("10 + 11"));
}

TEST(ExpressionClass_test, testcase_init_001)
{
    auto literalA1 = std::make_shared<LiteralExpr>();
    literalA1->literal = Token("10", "10", 0, TokenType::NUMBER);
    auto literalA2 = std::make_shared<LiteralExpr>();
    literalA2->literal = Token("11", "11", 0, TokenType::NUMBER);
    auto binaryA2 = std::make_shared<BinaryExpr>();
    binaryA2->op = Token("+", "+", 0, TokenType::PLUS);
    binaryA2->lOperand = literalA1;
    binaryA2->rOperand = literalA2;
    ASSERT_TRUE(binaryA2.get() != nullptr);
}