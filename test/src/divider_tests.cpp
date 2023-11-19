//
// Created by Konstantin Gredeskoul on 5/16/17.
//
//#include <vm.h>
#include <string>
#include "gtest/gtest.h"
#include "utility.h"
#include "config.h"

using namespace std;

double AddNumbers(const double a, const double b)
{
	return a + b;
}



TEST(TEST_FOR_PROJECT, test_001)
{
	ASSERT_EQ(AddNumbers(10, 1), 11);
	ASSERT_FALSE(g_loxSourceDir.empty());
}

TEST(Utility, JoinPath)
{
	auto path = Utility::PathJoin({g_loxSourceDir, "test", "lox"});
	std::string wanna = g_loxSourceDir + "/test/lox";
	ASSERT_EQ(path, wanna);
}

