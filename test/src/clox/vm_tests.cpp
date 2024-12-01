#include <string>
#include <gtest/gtest.h>


#include "chunk.h"  // 假设上面的代码保存在chunk.h文件中
#include "vm.h"
using namespace std;



class VmTestScaffold : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize tokens or other necessary setup before each test case

    }
};


TEST(VmTest, NormalInit_Ctor) {
    Vm vm;
    EXPECT_TRUE(true);
}