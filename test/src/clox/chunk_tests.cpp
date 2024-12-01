#include <string>
#include <gtest/gtest.h>


#include "chunk.h"  // 假设上面的代码保存在chunk.h文件中
#include "vm.h"
using namespace std;

TEST(ChunkTest, DefaultInitialization) {
    chunk testChunk;
    EXPECT_TRUE(testChunk.ops.empty());
    EXPECT_TRUE(testChunk.constValue.empty());
}

TEST(ChunkTest, AppendOpSingleOp) {
    chunk testChunk;

    // 创建一个操作码
    bytecode_type bytecode = {static_cast<uint8_t>(op_type::OP_CONSTANT), 42};
    testChunk.appendOp(bytecode);

    // 检查是否插入成功
    EXPECT_EQ(testChunk.ops.size(), 1);
    EXPECT_EQ(testChunk.readByteCode(0), bytecode);
    EXPECT_EQ(testChunk.readOp(0), static_cast<uint8_t>(op_type::OP_CONSTANT));
    EXPECT_EQ(testChunk.readOprand(0), 42);
}

TEST(ChunkTest, ReadOpAndOperand) {
    chunk testChunk;

    // 添加多个操作码
    testChunk.appendOp({static_cast<uint8_t>(op_type::OP_SUBTRACT), 5});
    testChunk.appendOp({static_cast<uint8_t>(op_type::OP_MULTIPLY), 3});

    // 逐一读取并验证
    EXPECT_EQ(testChunk.readOp(0), static_cast<uint8_t>(op_type::OP_SUBTRACT));
    EXPECT_EQ(testChunk.readOprand(0), 5);

    EXPECT_EQ(testChunk.readOp(1), static_cast<uint8_t>(op_type::OP_MULTIPLY));
    EXPECT_EQ(testChunk.readOprand(1), 3);
}

TEST(ChunkTest, AddAndRetrieveConstants) {
    chunk testChunk;

    // 添加常量值
    testChunk.constValue.push_back(3.14);
    testChunk.constValue.push_back(2.71);

    EXPECT_EQ(testChunk.constValue.size(), 2);
    EXPECT_DOUBLE_EQ(testChunk.constValue[0], 3.14);
    EXPECT_DOUBLE_EQ(testChunk.constValue[1], 2.71);
}

TEST(ChunkTest, BoolOperator) {
    chunk emptyChunk;

    chunk nonEmptyChunk;
    bytecode_type bytecode = {static_cast<uint8_t>(op_type::OP_RETURN), 0};
    nonEmptyChunk.appendOp(bytecode);
}

TEST(ChunkTest, FileNameAndLines) {
    chunk testChunk;

    testChunk.fileName = "test_file";
    testChunk.lines.push_back(10);
    testChunk.lines.push_back(20);

    EXPECT_EQ(testChunk.fileName, "test_file");
    ASSERT_EQ(testChunk.lines.size(), 2);
    EXPECT_EQ(testChunk.lines[0], 10);
    EXPECT_EQ(testChunk.lines[1], 20);
}