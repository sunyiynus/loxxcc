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


class ParserTest : public ::testing::Test {
protected:
    Tokens tokens;
    Parser parser;

    void SetUp() override {
        // Initialize tokens or other necessary setup before each test case
        string src = "a + b / 2 * 10 + 4 - 10;    ";
        Scanner lexer(src);
        tokens = lexer.scanTokens();
        parser = Parser(tokens);
    }

    Token createToken(TokenType type, std::string lexeme) {
        return Token(lexeme, lexeme, 0, type);
    }
};

// Test for the constructor with tokens
TEST_F(ParserTest, ConstructorWithTokens) {
    ASSERT_EQ(parser.current(), tokens.front());
    auto res = parser.parse();
    ASSERT_EQ(res.size(), 1);
}

class ParserTestScaffold : public ::testing::Test {
protected:
    Tokens tokens;
    Parser parser;

    void SetUp() override {
        // Initialize tokens or other necessary setup before each test case
        string src = Utility::ReadFile(Utility::PathJoin({g_loxSourceDir, "test", "lox", "parser_test.lox"}));
        Scanner lexer(src);
        tokens = lexer.scanTokens();
        parser = Parser(tokens);
    }

    Token createToken(TokenType type, std::string lexeme) {
        return Token(lexeme, lexeme, 0, type);
    }
};

TEST_F(ParserTestScaffold, DefaultConstructor) {
    ASSERT_GT(tokens.size(), 20);
    auto res = parser.parse();
    ASSERT_TRUE(parser.atEnd());
    ASSERT_EQ(res.size(), 2);
}

// // Test the `current` method
// TEST_F(ParserTest, CurrentToken) {
//     tokens.push_back(createToken(TokenType::NUMBER, "1"));
//     parser = Parser(tokens);
//     ASSERT_EQ(parser.current(), tokens.front());
// }

// // Test the `previous` method
// TEST_F(ParserTest, PreviousToken) {
//     tokens = { createToken(TokenType::NUMBER, "1"), createToken(TokenType::PLUS, "+") };
//     parser = Parser(tokens);
//     parser.advance();
//     ASSERT_EQ(parser.previous().token, TokenType::NUMBER);
// }

// // Test the `atEnd` method
// TEST_F(ParserTest, AtEnd) {
//     parser = Parser(tokens);  // Empty tokens
//     ASSERT_TRUE(parser.atEnd());

//     tokens.push_back(createToken(TokenType::NUMBER, "1"));
//     parser = Parser(tokens);
//     ASSERT_FALSE(parser.atEnd());
// }

// // Test the `matchTokens` method
// TEST_F(ParserTest, MatchTokens) {
//     tokens = { createToken(TokenType::NUMBER, "1"), createToken(TokenType::PLUS, "+") };
//     parser = Parser(tokens);

//     ASSERT_TRUE(parser.matchTokens({TokenType::NUMBER}));
//     ASSERT_EQ(parser.current().type, TokenType::PLUS);
// }

// // Test `advance` method
// TEST_F(ParserTest, Advance) {
//     tokens = { createToken(TokenType::NUMBER, "1"), createToken(TokenType::PLUS, "+") };
//     parser = Parser(tokens);

//     parser.advance();
//     ASSERT_EQ(parser.current().type, TokenType::PLUS);
// }

// // Test the `synchronize` method
// TEST_F(ParserTest, Synchronize) {
//     tokens = { createToken(TokenType::NUMBER, "1"), createToken(TokenType::PLUS, "+"), createToken(TokenType::SEMICOLON, ";") };
//     parser = Parser(tokens);

//     parser.synchronize();
//     ASSERT_EQ(parser.current().type, TokenType::SEMICOLON);
// }

// // Test `consume` for correct type
// TEST_F(ParserTest, ConsumeValidToken) {
//     tokens = { createToken(TokenType::NUMBER, "1") };
//     parser = Parser(tokens);

//     ASSERT_NO_THROW(parser.consume({TokenType::NUMBER}));
// }

// // Test `consume` for incorrect type
// TEST_F(ParserTest, ConsumeInvalidToken) {
//     tokens = { createToken(TokenType::PLUS, "+") };
//     parser = Parser(tokens);

//     ASSERT_ANY_THROW(parser.consume({TokenType::NUMBER}));
// }

// // Test `binary_expression_reimpl` helper function
// TEST_F(ParserTest, BinaryExpressionReimpl) {
//     tokens = { createToken(TokenType::NUMBER, "1"), createToken(TokenType::PLUS, "+"), createToken(TokenType::NUMBER, "2") };
//     parser = Parser(tokens);

//     auto expr = parser.binary_expression_reimpl<&Parser::primary>({TokenType::PLUS});
//     ASSERT_TRUE(expr != nullptr);
// }

// // Corner cases
// TEST_F(ParserTest, NoTokensAdvance) {
//     Parser emptyParser;
//     ASSERT_NO_THROW(emptyParser.advance());
//     ASSERT_TRUE(emptyParser.atEnd());
// }

// TEST_F(ParserTest, NoTokensCurrent) {
//     Parser emptyParser;
//     ASSERT_THROW(emptyParser.current(), std::out_of_range);
// }

// TEST_F(ParserTest, EmptyMatchTokens) {
//     ASSERT_FALSE(parser.matchTokens({TokenType::NUMBER}));
// }

// TEST_F(ParserTest, MultipleAdvanceBeyondEnd) {
//     tokens = { createToken(TokenType::NUMBER, "1") };
//     parser = Parser(tokens);
//     parser.advance();
//     parser.advance();
//     ASSERT_TRUE(parser.atEnd());
// }

// TEST_F(ParserTest, SynchronizeWithNoTokens) {
//     Parser emptyParser;
//     ASSERT_NO_THROW(emptyParser.synchronize());
//     ASSERT_TRUE(emptyParser.atEnd());
// }

// TEST_F(ParserTest, BinaryExpressionNoOperands) {
//     tokens = { createToken(TokenType::PLUS, "+") };
//     parser = Parser(tokens);
//     auto expr = parser.binary_expression_reimpl<&Parser::primary>({TokenType::PLUS});
//     ASSERT_TRUE(expr == nullptr);
// }

// // Test `parse` method to parse an empty statement list
// TEST_F(ParserTest, ParseEmptyStatementList) {
//     Parser emptyParser;
//     auto statements = emptyParser.parse();
//     ASSERT_TRUE(statements.empty());
// }



TEST(ParserClass_test, testcase_expression_001)
{
    string src = "a + b / 2 * 10 + 4 - 10;    ";
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 12);
    Parser parser(tokens);
    auto ast = parser.parse();
    ASSERT_EQ(ast.size(), 1);
}


// TEST(ParserClass_test, testcase_expression_002)
// {
//     string src = "a + b / 2 * 10 + (4 - 10);    ";
//     ASSERT_FALSE(src.empty());
//     Scanner lexer(src);
//     auto tokens = lexer.scanTokens();
//     ASSERT_EQ(tokens.size(), 14);
//     Parser parser(tokens);
//     auto ast = parser.parse();
//     Printer printer;
//     ASSERT_TRUE(ast.get() != nullptr);
//     auto res = ast->accept(&printer);
//     cout << res->resultStr << endl;
//     ASSERT_EQ(res->resultStr, std::string("a + b / 2 * 10 + ( 4 - 10 )"));
// }


// TEST(ParserClass_test, testcase_expression_003)
// {
//     string src = "(a + b) / ((2 * 10) + (4 - 10));    ";
//     ASSERT_FALSE(src.empty());
//     Scanner lexer(src);
//     auto tokens = lexer.scanTokens();
//     ASSERT_EQ(tokens.size(), 20);
//     Parser parser(tokens);
//     auto ast = parser.parse();
//     Printer printer;
//     ASSERT_TRUE(ast.get() != nullptr);
//     auto res = ast->accept(&printer);
//     cout << res->resultStr << endl;
//     ASSERT_EQ(res->resultStr, std::string("( a + b ) / ( ( 2 * 10 ) + ( 4 - 10 ) )"));
// }