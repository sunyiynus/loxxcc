#include <string>
#include <random>
#include <gtest/gtest.h>
#include "Utility.h"
#include "types.h"
#include "config.h"
#include "scanner.h"
#include "parser.h"
#include "interpreter.h"
#include "printer.h"
#include "testscaffold.h"

using namespace std;


TEST(EvaluatorClass_test, testcase_expression_001)
{
    // string src = "1 + 2; 2 + 3; 3 + 3;    ";
    // ASSERT_FALSE(src.empty());
    // Scanner lexer(src);
    // auto tokens = lexer.scanTokens();
    // ASSERT_EQ(tokens.size(), 12);
    // Parser parser(tokens);
    // auto ast = parser.parse();
    // ASSERT_EQ(ast.size(), 3);

    // Interpreter interpreter;
    // std::vector<AnyResult::ptr> resultVec;
    // for (const auto& stmt: ast) {
    //     resultVec.push_back(stmt->accept(&interpreter));
    // }
    // ASSERT_FALSE(resultVec.empty());
    // ASSERT_EQ(resultVec.size(), 3);
    // ASSERT_EQ(resultVec[0]->type, prim_type::Number);
    // ASSERT_TRUE(resultVec[0]->value);
    // ASSERT_DOUBLE_EQ(resultVec[0]->value.get<number>(), 3);
    // ASSERT_DOUBLE_EQ(resultVec[1]->value.get<number>(), 5);
    // ASSERT_DOUBLE_EQ(resultVec[2]->value.get<number>(), 6);
    
}

TEST(EvaluatorClass_test, testcase_expression_002)
{
    string src = "-100 - 1; -20 + 10;  100 / 5; 200 * 4;";
    ASSERT_FALSE(src.empty());
    Scanner lexer(src);
    auto tokens = lexer.scanTokens();
    Parser parser(tokens);
    auto ast = parser.parse();
    ASSERT_EQ(ast.size(), 4);

    Interpreter interpreter;
    std::vector<AnyResult::ptr> resultVec;
    for (const auto& stmt: ast) {
        resultVec.push_back(stmt->accept(&interpreter));
    }
    ASSERT_FALSE(resultVec.empty());
    ASSERT_EQ(resultVec.size(), 4);
    ASSERT_EQ(resultVec[0]->type, prim_type::Number);
    ASSERT_TRUE(resultVec[0]->value);
    ASSERT_DOUBLE_EQ(resultVec[0]->value.get<number>(), -101);
    ASSERT_DOUBLE_EQ(resultVec[1]->value.get<number>(), -10);
    ASSERT_DOUBLE_EQ(resultVec[2]->value.get<number>(), 20);
    ASSERT_DOUBLE_EQ(resultVec[3]->value.get<number>(), 800);
}


TEST_F(ParserTestScaffold, evaluate_associativity) {
    auto filePath = "test/lox/assignment/associativity.lox";
    loadLoxCodeFromFile(filePath);
    ASSERT_GT(tokens.size(), 4);
    ASSERT_TRUE(parser.atEnd());
    astprinter.execute(stmts);
    writeToDotFile();

    interpreter.interprete(stmts);
    ASSERT_FALSE(ossExec.str().empty());
    ASSERT_EQ(ossExec.str(), "c\nc\nc\n") << oss.str();
    
}


TEST_F(ParserTestScaffold, evaluate_parser_test) {
    std::string filePath = "test/lox/parser_test.lox";
    loadLoxCodeFromFile(filePath);
    ASSERT_GT(tokens.size(), 20);
    ASSERT_TRUE(parser.atEnd());
    astprinter.execute(stmts);
    writeToDotFile();
    interpreter.interprete(stmts);
    ASSERT_FALSE(oss.str().empty());
    // ASSERT_EQ(oss.str(), "a\nb\nc\n") << oss.str();
    
}


TEST_F(ParserTestScaffold, evaluate_parser_if_stmt_test_if_lox) {
    std::string filePath =  "test/lox/if/if.lox";
    loadLoxCodeFromFile(filePath);
    ASSERT_GT(tokens.size(), 20);
    ASSERT_TRUE(parser.atEnd());
    astprinter.execute(stmts);
    writeToDotFile();
    // interpreter.interprete(stmts);
    // ASSERT_FALSE(oss.str().empty());
    // std::cout << oss.str();
    // ASSERT_EQ(oss.str(), "a\nb\nc\n") << oss.str();
    
}

TEST_F(ParserTestScaffold, evaluate_parser_if_stmt_test_var_in_else_lox) {
    std::string filePath = "test/lox/if/var_in_else.lox";
    loadLoxCodeFromFile(filePath);
    ASSERT_GT(tokens.size(), 2);
    ASSERT_TRUE(parser.atEnd());
    astprinter.execute(stmts);
    writeToDotFile();
    // interpreter.interprete(stmts);
    // ASSERT_FALSE(oss.str().empty());
    // std::cout << oss.str();
    // ASSERT_EQ(oss.str(), "a\nb\nc\n") << oss.str();
    
}

TEST_F(ParserTestScaffold, evaluate_parser_if_stmt_test_var_in_then_lox) {
    const std::string srcFile = "test/lox/if/var_in_then.lox";
    loadLoxCodeFromFile(srcFile);
    ASSERT_GT(tokens.size(), 2);
    ASSERT_TRUE(parser.atEnd());
    astprinter.execute(stmts);
    writeToDotFile();
    // interpreter.interprete(stmts);
    // ASSERT_FALSE(oss.str().empty());
    // std::cout << oss.str();
    // ASSERT_EQ(oss.str(), "a\nb\nc\n") << oss.str();
    
}

TEST_F(ParserTestScaffold, evaluate_parser_for_stmt_test_break_continue_lox) {
    const std::string srcFile = "test/lox/for/break_continue.lox";
    loadLoxCodeFromFile(srcFile);
    ASSERT_GT(tokens.size(), 2);
    ASSERT_TRUE(parser.atEnd());
    astprinter.execute(stmts);
    writeToDotFile();
    // interpreter.interprete(stmts);
    // ASSERT_FALSE(oss.str().empty());
    // std::cout << oss.str();
    // ASSERT_EQ(oss.str(), "a\nb\nc\n") << oss.str();
}

TEST_F(ParserTestScaffold, evaluate_parser_while_stmt_test_break_continue_lox) {
    const std::string srcFile = "test/lox/while/break_continue.lox";
    loadLoxCodeFromFile(srcFile);
    ASSERT_GT(tokens.size(), 2);
    ASSERT_TRUE(parser.atEnd());
    astprinter.execute(stmts);
    writeToDotFile();
    // interpreter.interprete(stmts);
    // ASSERT_FALSE(oss.str().empty());
    // std::cout << oss.str();
    // ASSERT_EQ(oss.str(), "a\nb\nc\n") << oss.str();
    
}


TEST_F(ParserTestScaffold, evaluate_parser_while_stmt_test_syntax_lox) {
    const std::string srcFile = "test/lox/while/syntax.lox";
    loadLoxCodeFromFile(srcFile);
    ASSERT_GT(tokens.size(), 2);
    ASSERT_TRUE(parser.atEnd());
    astprinter.execute(stmts);
    writeToDotFile();
    // interpreter.interprete(stmts);
    // ASSERT_FALSE(oss.str().empty());
    // std::cout << oss.str();
    // ASSERT_EQ(oss.str(), "a\nb\nc\n") << oss.str();
}


TEST_F(ParserTestScaffold, evaluate_parser_for_stmt_test_syntax_lox) {
    const std::string srcFile = "test/lox/for/syntax.lox";
    loadLoxCodeFromFile(srcFile);
    ASSERT_GT(tokens.size(), 2);
    ASSERT_TRUE(parser.atEnd());
    astprinter.execute(stmts);
    writeToDotFile();
    // interpreter.interprete(stmts);
    // ASSERT_FALSE(oss.str().empty());
    // std::cout << oss.str();
    // ASSERT_EQ(oss.str(), "a\nb\nc\n") << oss.str();
}