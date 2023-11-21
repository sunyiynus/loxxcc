
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
    auto ff = Format::format("name{1}name\n") % 1;
    ASSERT_EQ(ff.getFieldList().size(),0);
    ff.toString();
    ASSERT_EQ(ff.getFieldList().size(),3);
}

TEST(format, SplitsTest_1)
{
    auto ff = Format::format("{}name{1}name\n") % 1 % 2;
    ASSERT_EQ(ff.getFieldList().size(),0);
    ff.toString();
    ASSERT_EQ(ff.getFieldList().size(),4);
}

TEST(format, SplitsTest_2)
{
    auto ff = Format::format("{1}{2}{3}name{}{}\n") % 1 % 1;
    ASSERT_EQ(ff.getFieldList().size(),0);
    ff.toString();
    ASSERT_EQ(ff.getFieldList().size(),7);
}