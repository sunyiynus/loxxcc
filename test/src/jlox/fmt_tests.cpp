

#include <gtest/gtest.h>
#include "format.h"  // 假设您的类定义在此头文件中

// 测试基本的字符串格式化功能
TEST(BasicFormatTest, BasicStringFormatting) {
    auto formatter = Format::format("Hello, {}!");
    formatter % "World";
    EXPECT_EQ(formatter.toString(), "Hello, World!");
}

// 测试多个占位符的替换
TEST(BasicFormatTest, MultiplePlaceholders) {
    auto formatter = Format::format("{} + {} = {}");
    formatter % 1 % 2 % 3;
    EXPECT_EQ(formatter.toString(), "1 + 2 = 3");
}

// 测试占位符数量与参数数量不匹配的情况
TEST(BasicFormatTest, PlaceholderArgumentMismatch) {
    auto formatter = Format::format("{} + {} = {}");
    formatter % 1 % 2;
    EXPECT_THROW(formatter.toString(), std::out_of_range);
}

// 测试没有占位符的字符串
TEST(BasicFormatTest, NoPlaceholders) {
    auto formatter = Format::format("No placeholders here.");
    EXPECT_EQ(formatter.toString(), "No placeholders here.");
}

// 测试连续的占位符
TEST(BasicFormatTest, ConsecutivePlaceholders) {
    auto formatter = Format::format("{}{}{}");
    formatter % "A" % "B" % "C";
    EXPECT_EQ(formatter.toString(), "ABC");
}

// 测试占位符中包含特殊字符
TEST(BasicFormatTest, SpecialCharactersInPlaceholder) {
    auto formatter = Format::format("Special chars: {}");
    formatter % "!@#$%^&*()";
    EXPECT_EQ(formatter.toString(), "Special chars: !@#$%^&*()");
}

// 测试占位符中包含数字
TEST(BasicFormatTest, NumericPlaceholders) {
    auto formatter = Format::format("Numbers: {} {} {}");
    formatter % 10 % 20.5 % -30;
    EXPECT_EQ(formatter.toString(), "Numbers: 10 20.500000 -30");
}

// 测试占位符中包含布尔值
TEST(BasicFormatTest, BooleanPlaceholders) {
    auto formatter = Format::format("Booleans: {} {}");
    formatter % true % false;
    EXPECT_EQ(formatter.toString(), "Booleans: 1 0");
}

// 测试占位符中包含字符
TEST(BasicFormatTest, CharPlaceholders) {
    auto formatter = Format::format("Chars: {} {}");
    formatter % 'A' % 'Z';
    EXPECT_EQ(formatter.toString(), "Chars: A Z");
}

// 测试占位符中包含字符串
TEST(BasicFormatTest, StringPlaceholders) {
    auto formatter = Format::format("Strings: {} and {}");
    formatter % std::string("Hello") % std::string("World");
    EXPECT_EQ(formatter.toString(), "Strings: Hello and World");
}

// 测试占位符中包含混合类型
TEST(BasicFormatTest, MixedTypePlaceholders) {
    auto formatter = Format::format("{} is {} years old and has {} dollars.");
    formatter % "Alice" % 30 % 100.50;
    EXPECT_EQ(formatter.toString(), "Alice is 30 years old and has 100.500000 dollars.");
}

// 测试占位符中包含负数
TEST(BasicFormatTest, NegativeNumbers) {
    auto formatter = Format::format("Negative number: {}");
    formatter % -42;
    EXPECT_EQ(formatter.toString(), "Negative number: -42");
}

// 测试占位符中包含大数字
TEST(BasicFormatTest, LargeNumbers) {
    auto formatter = Format::format("Large number: {}");
    formatter % 1234567890;
    EXPECT_EQ(formatter.toString(), "Large number: 1234567890");
}

// 测试占位符中包含浮点数
TEST(BasicFormatTest, FloatingPointNumbers) {
    auto formatter = Format::format("Floating point: {}");
    formatter % 3.14159;
    EXPECT_EQ(formatter.toString(), "Floating point: 3.141590");
}

// 测试占位符中包含科学计数法
TEST(BasicFormatTest, ScientificNotation) {
    auto formatter = Format::format("Scientific notation: {}");
    formatter % 1.23e4;
    EXPECT_EQ(formatter.toString(), "Scientific notation: 12300.000000");
}

// 测试占位符中包含空字符串
TEST(BasicFormatTest, EmptyStringPlaceholder) {
    auto formatter = Format::format("Empty string: {}");
    formatter % "";
    EXPECT_EQ(formatter.toString(), "Empty string: ");
}

// 测试占位符中包含空格
TEST(BasicFormatTest, WhitespacePlaceholder) {
    auto formatter = Format::format("Whitespace: '{}'");
    formatter % "   ";
    EXPECT_EQ(formatter.toString(), "Whitespace: '   '");
}

// 测试占位符中包含转义字符
TEST(BasicFormatTest, EscapeCharacters) {
    auto formatter = Format::format("Escape: {}");
    formatter % "\n\t\\";
    EXPECT_EQ(formatter.toString(), "Escape: \n\t\\");
}

// 测试占位符中包含长字符串
TEST(BasicFormatTest, LongStringPlaceholder) {
    std::string longStr(1000, 'a');
    auto formatter = Format::format("Long string: {}");
    formatter % longStr;
    EXPECT_EQ(formatter.toString(), "Long string: " + longStr);
}

// 测试占位符中包含多个相同的参数
TEST(BasicFormatTest, RepeatedArguments) {
    auto formatter = Format::format("{} {} {}");
    formatter % "repeat" % "repeat" % "repeat";
    EXPECT_EQ(formatter.toString(), "repeat repeat repeat");
}

// 测试占位符中包含多个不同的参数
TEST(BasicFormatTest, DifferentArguments) {
    auto formatter = Format::format("{} {} {}");
    formatter % "first" % "second" % "third";
    EXPECT_EQ(formatter.toString(), "first second third");
}

// 测试占位符中包含参数顺序错误
TEST(BasicFormatTest, ArgumentOrderMismatch) {
    auto formatter = Format::format("{} {} {}");
    formatter % "first" % "second";
    EXPECT_THROW(formatter.toString(), std::out_of_range);
}

// 测试占位符中包含多余的参数
TEST(BasicFormatTest, ExtraArguments) {
    auto formatter = Format::format("{} {}");
    formatter % "first" % "second" % "third";
    
}
 
