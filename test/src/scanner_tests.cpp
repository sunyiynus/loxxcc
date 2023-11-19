
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
    auto ff = Format::format("name{1}\n") % 1;
    ASSERT_EQ(ff.getFieldList().size(),2);

}