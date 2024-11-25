project(clox_unittests)

include_directories(${LOXXVM_HEADERS_DIR})
include_directories(${LOXXCC_INSTALL_INCLUDE_DIR})

# 指定源文件所在的目录
set(TEST_SOURCE_DIR ${CMAKE_SOURCE_DIR}/test/src/clox)
message(${TEST_SOURCE_DIR})
# 自动收集 src 目录下所有的 .cpp 文件
file(GLOB SOURCES ${TEST_SOURCE_DIR}/*.cpp)

add_executable(clox_utests ${SOURCES})
target_link_libraries(clox_utests gtest_main)


# 设置目标的输出目录到 bin 目录
set_target_properties(clox_utests PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${LOXXCC_INSTALL_BIN_DIR}
)
