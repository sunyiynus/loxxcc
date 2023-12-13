#include <string>
#include "gtest/gtest.h"
#include "variant.h"

using namespace std;




TEST(VariantClass_test, testcase_init_001)
{
    ASSERT_TRUE(true);
    Variant<int, char, std::string> v;
}