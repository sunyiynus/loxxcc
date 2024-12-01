#include <string>
#include <gtest/gtest.h>

#include "compile.h"


using namespace std;



TEST(CompilerTest, NormalTest_init_ctor)
{
    Compiler compiler;
    EXPECT_TRUE(compiler.end());
}


