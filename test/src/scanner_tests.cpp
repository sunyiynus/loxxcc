
#include "gtest/gtest.h"
#include "scanner.h"
#include "Utility.h"
#include "config.h"
#include "format.h"

using namespace std;



TEST(ReadFile_Test, ReadSomeFile)
{
    auto src = Utility::ReadFile(Utility::PathJoin({g_loxSourceDir, "test", "lox", "bench", "binary_trees.lox"}));
    ASSERT_FALSE(src.empty());
}

TEST(scanner_Test, SrcInit)
{
    auto src = Utility::ReadFile(Utility::PathJoin({g_loxSourceDir, "test", "lox", "bench", "binary_trees.lox"}));
    Scanner scan(src);
    ASSERT_TRUE(true);
}


TEST(format, Init)
{
    auto ff = Format::format("name{1}") % 1;
    ASSERT_EQ(ff.getFieldList().size(),0);
    ff.toString();
    ASSERT_EQ(ff.getFieldList().size(),2);
}

TEST(format, SplitsTest)
{
    auto ff = Format::format("name{1}name\n") % 21;
    ASSERT_EQ(ff.getFieldList().size(),0);
    ASSERT_EQ(ff.toString(), std::string("name21name\n"));
    ASSERT_EQ(ff.getFieldList().size(),3);
}

TEST(format, SplitsTest_1)
{
    auto ff = Format::format("{}name{1}name\n") % 1 % 2;
    ASSERT_EQ(ff.getFieldList().size(),0);
    ASSERT_EQ(ff.toString(), std::string("1name2name\n"));
    ASSERT_EQ(ff.getFieldList().size(),4);
}

TEST(format, SplitsTest_2)
{
    auto ff = Format::format("{1}{2}{3}name{}{}\n") % 1 % 2 % 3 % 4 % 5 % 6;
    ASSERT_EQ(ff.getFieldList().size(),0);
    ASSERT_EQ(ff.toString(), std::string("123name45\n"));
    ASSERT_EQ(ff.getFieldList().size(),7);

    std::ostringstream isn;
    isn << Format::format("{1}{2}{3}name{}{}\n") % 1 % 2 % 3 % 4 % 5 % 6;
    std::cout << isn.str();
}


TEST(ScannerClass_test, testcase_ctor_001)
{
    auto src = Utility::ReadFile(Utility::PathJoin({g_loxSourceDir, "test", "lox", "assignment", "to_this.lox"}));
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    ASSERT_FALSE(tokens.empty());
    ASSERT_EQ(tokens.size(), 17);
    ASSERT_EQ(tokens[16].lexeme, string(";"));
}

TEST(ScannerClass_test, testcase_identifer_001)
{
    string src = "a = 1000;";
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 4);
    ASSERT_EQ(tokens[2].lexeme, string("1000"));
    ASSERT_EQ(tokens[3].lexeme, string(";"));
}

TEST(ScannerClass_test, testcase_identifer_002)
{
    string src = "a1adldkjfal_001233=1000;";
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 4);
    ASSERT_EQ(tokens[2].lexeme, string("1000"));
    ASSERT_EQ(tokens[3].lexeme, string(";"));
}

TEST(ScannerClass_test, testcase_identifer_003)
{
    string src = "a1adldkjfal_001233=1000.1000;    ";
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 4);
    ASSERT_EQ(tokens[2].lexeme, string("1000.1000"));
    ASSERT_EQ(tokens[2].token, TokenType::NUMBER);
    ASSERT_EQ(tokens[3].lexeme, string(";"));
}

TEST(ScannerClass_test, testcase_identifer_004)
{
    string src = "a1adldkjfal_001233= \"abcdefj\";    ";
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 4);
    ASSERT_EQ(tokens[2].lexeme, string("abcdefj"));
    ASSERT_EQ(tokens[2].token, TokenType::STRING);
    ASSERT_EQ(tokens[3].lexeme, string(";"));
}

TEST(ScannerClass_test, testcase_identifer_005)
{
    string src = "a1adldkjfal_001233= \"abcdefj\";    ";
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 4);
    ASSERT_EQ(tokens[2].lexeme, string("abcdefj"));
    ASSERT_EQ(tokens[2].token, TokenType::STRING);
    ASSERT_EQ(tokens[3].lexeme, string(";"));
}

TEST(ScannerClass_test, testcase_expression_001)
{
    string src = "a1 = a + b / 2 * 10 + 4 - 10;    ";
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 14);
    ASSERT_EQ(tokens[2].lexeme, string("a"));
    ASSERT_EQ(tokens[2].token, TokenType::IDENTIFIER);
    ASSERT_EQ(tokens[3].lexeme, string("+"));
    ASSERT_EQ(tokens[12].lexeme, string("10"));
}

TEST(ScannerClass_test, testcase_expression_002)
{
    string src = "a1 =  -10.2 ;   ";
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 4);
    ASSERT_EQ(tokens[2].lexeme, string("-10.2"));
    ASSERT_EQ(tokens[2].token, TokenType::NUMBER);
}

TEST(ScannerClass_test, testcase_vars_001)
{
    string src = "var a1 =  -10.2 ;   ";
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 5);
    ASSERT_EQ(tokens[3].lexeme, string("-10.2"));
    ASSERT_EQ(tokens[3].token, TokenType::NUMBER);
    ASSERT_EQ(tokens[0].token, TokenType::VAR);
}

TEST(ScannerClass_test, testcase_keyword_001)
{
    string src = "var idx = 0; while ( idx < 10) { idx = idx + 1; if (idx == 2) {continue;}}";
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 29);
    ASSERT_EQ(tokens[3].lexeme, string("0"));
    ASSERT_EQ(tokens[3].token, TokenType::NUMBER);
    ASSERT_EQ(tokens[0].token, TokenType::VAR);
    ASSERT_EQ(tokens[1].token, TokenType::IDENTIFIER);
    ASSERT_EQ(tokens[5].token, TokenType::WHILE);
}

TEST(ScannerClass_test, testcase_keyword_002)
{
    string src = "fn func_01(i, m) {var idx = 0; while ( idx < 10) { idx = idx + 1; if (idx == 2) {continue;}} return 0;}";
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 41);
    ASSERT_EQ(tokens[3].lexeme, string("i"));
    ASSERT_EQ(tokens[3].token, TokenType::IDENTIFIER);
    ASSERT_EQ(tokens[0].token, TokenType::FUNC);
    ASSERT_EQ(tokens[1].token, TokenType::IDENTIFIER);
    ASSERT_EQ(tokens[5].token, TokenType::IDENTIFIER);
    ASSERT_EQ(tokens[4].token, TokenType::COMMA);
    ASSERT_EQ(tokens[37].token, TokenType::RETURN);
}

void PrintTokens(const vector<Token>& tokens) {
    int cnt = 1;
    for (const auto& token: tokens) {
        std::cout << token.lexeme << " ";
        if (cnt % 10 == 0) {
            std::cout << std::endl;
        }
        cnt++;
    }
    std::cout << std::endl;
}


TEST(ScannerClass_test, testcase_keyword_003)
{
    auto src = Utility::ReadFile(Utility::PathJoin({g_loxSourceDir, "test", "lox", "normal.lox"}));
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    PrintTokens(tokens);
    ASSERT_EQ(tokens.size(), 81);
    ASSERT_EQ(tokens[3].lexeme, string("fn"));
    ASSERT_EQ(tokens[3].token, TokenType::FUNC);
    ASSERT_EQ(tokens[0].token, TokenType::CLASS);
    ASSERT_EQ(tokens[1].token, TokenType::IDENTIFIER);
    ASSERT_EQ(tokens[6].token, TokenType::IDENTIFIER);
    ASSERT_EQ(tokens[4].token, TokenType::IDENTIFIER);
    ASSERT_EQ(tokens[73].token, TokenType::RIGHT_PAREN);

}