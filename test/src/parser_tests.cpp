#include <string>
#include <gtest/gtest.h>
#include "Utility.h"
#include "config.h"
#include "format.h"
#include "expression.h"
#include "scanner.h"
#include "parser.h"
#include "printer.h"

using namespace std;

TEST(ParserClass_test, testcase_expression_001)
{
    string src = "a + b / 2 * 10 + 4 - 10;    ";
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 12);
    Parser parser(tokens);
    auto ast = parser.parse();
    Printer printer;
    ASSERT_TRUE(ast.get() != nullptr);
    auto res = ast->accept(&printer);
    cout << res->resultStr << endl;
    ASSERT_EQ(res->resultStr, std::string("a + b / 2 * 10 + 4 - 10"));
}


TEST(ParserClass_test, testcase_expression_002)
{
    string src = "a + b / 2 * 10 + (4 - 10);    ";
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 14);
    Parser parser(tokens);
    auto ast = parser.parse();
    Printer printer;
    ASSERT_TRUE(ast.get() != nullptr);
    auto res = ast->accept(&printer);
    cout << res->resultStr << endl;
    ASSERT_EQ(res->resultStr, std::string("a + b / 2 * 10 + ( 4 - 10 )"));
}


TEST(ParserClass_test, testcase_expression_003)
{
    string src = "(a + b) / ((2 * 10) + (4 - 10));    ";
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 20);
    Parser parser(tokens);
    auto ast = parser.parse();
    Printer printer;
    ASSERT_TRUE(ast.get() != nullptr);
    auto res = ast->accept(&printer);
    cout << res->resultStr << endl;
    ASSERT_EQ(res->resultStr, std::string("( a + b ) / ( ( 2 * 10 ) + ( 4 - 10 ) )"));
}