#include <string>
#include "gtest/gtest.h"
#include "variant.h"

using namespace std;


// 测试类：Variant 是否正确存储 int 类型
TEST(VariantTest, HoldsIntType) {
    Variant v = 42;  // 存储一个 int 类型
    ASSERT_TRUE(v.holdsAlternative<int>());  // 应该持有 int 类型
    EXPECT_EQ(v.get<int>(), 42);  // 获取并检查值是否为 42
}

// 测试类：Variant 是否正确存储 string 类型
TEST(VariantTest, HoldsStringType) {
    Variant v = std::string("Hello, Variant!");  // 存储一个 string 类型
    ASSERT_TRUE(v.holdsAlternative<std::string>());  // 应该持有 string 类型
    EXPECT_EQ(v.get<std::string>(), "Hello, Variant!");  // 获取并检查值
}

// 测试类：Variant 类型不匹配时，get 方法应抛出 std::bad_cast
TEST(VariantTest, GetThrowsBadCastForWrongType) {
    Variant v = 42;  // 存储一个 int 类型
    ASSERT_THROW(v.get<std::string>(), std::bad_cast);  // 获取 string 类型时抛出 std::bad_cast 异常
}

// 测试类：空的 Variant 应该返回 "Empty variant!"
TEST(VariantTest, EmptyVariantPrint) {
    Variant v;  // 默认构造一个空的 Variant
    testing::internal::CaptureStdout();  // 捕获输出
    v.print();  // 应该输出 "Empty variant!"
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Empty variant!\n");
}

// 测试类：多次赋值给 Variant，确保正确管理内存
TEST(VariantTest, Assignment) {
    Variant v1 = 42;
    Variant v2 = std::string("Hello");
    
    v2 = v1;  // 赋值给 v2
    ASSERT_TRUE(v2.holdsAlternative<int>());  // v2 现在应该持有 int 类型
    EXPECT_EQ(v2.get<int>(), 42);  // 检查 v2 存储的值是否为 42
}

// 测试类：Variant 支持移动构造
TEST(VariantTest, MoveConstructor) {
    Variant v1 = 42;  // 存储一个 int 类型
    Variant v2 = std::move(v1);  // 使用移动构造
    ASSERT_TRUE(v2.holdsAlternative<int>());
    EXPECT_EQ(v2.get<int>(), 42);
    ASSERT_FALSE(v1.holdsAlternative<int>());  // v1 应该已经被移动，空
}

// 测试类：Variant 支持移动赋值
TEST(VariantTest, MoveAssignment) {
    Variant v1 = 42;
    Variant v2 = std::string("Hello");
    v2 = std::move(v1);  // 使用移动赋值
    ASSERT_TRUE(v2.holdsAlternative<int>());
    EXPECT_EQ(v2.get<int>(), 42);
    ASSERT_FALSE(v1.holdsAlternative<int>());  // v1 应该已经被移动，空
}
