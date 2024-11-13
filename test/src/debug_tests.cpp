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


TEST_F(ParserTestScaffold, DefaultConstructor) {
    auto filePath = Utility::PathJoin({g_loxSourceDir, "test", "lox", "parser_test.lox"});
    loadLoxCodeFromFile(filePath);
    ASSERT_GT(tokens.size(), 20);
    ASSERT_TRUE(parser.atEnd());
    astprinter.execute(stmts);
    writeToDotFile(astprinter.generateDot());


    interpreter.interprete(stmts);
    ASSERT_FALSE(oss.str().empty());
    // ASSERT_EQ(oss.str(), "a\nb\nc\n") << oss.str();
    
}