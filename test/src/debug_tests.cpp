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


TEST_F(ParserTestScaffold, evaluate_parser_for_stmt_test_syntax_lox) {
    const std::string srcFile = "test/lox/debug.lox";
    auto filePath = Utility::PathJoin({g_loxSourceDir, srcFile});
    loadLoxCodeFromFile(filePath);
    ASSERT_GT(tokens.size(), 2);
    ASSERT_TRUE(parser.atEnd());
    astprinter.execute(stmts);
    writeToDotFile(astprinter.generateDot(srcFile));
    // interpreter.interprete(stmts);
    // ASSERT_FALSE(oss.str().empty());
    // std::cout << oss.str();
    // ASSERT_EQ(oss.str(), "a\nb\nc\n") << oss.str();
}