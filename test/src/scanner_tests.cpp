
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