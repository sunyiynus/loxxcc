cmake_minimum_required(VERSION 3.2)
project(divider_tests)

# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

include_directories(${LOXXCC_HEADERS_DIR})
include_directories(${LOXXCC_INSTALL_INCLUDE_DIR})

set(SOURCE_FILES main.cpp 
                 src/divider_tests.cpp
                 src/expression_tests.cpp
                 src/parser_tests.cpp
                 src/variant_tests.cpp
                 src/scanner_tests.cpp)

add_executable(divider_tests ${SOURCE_FILES})
target_link_libraries(divider_tests gtest loxcompile)
target_include_directories(divider_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/extern/googletest/googletest/include
)

# 设置目标的输出目录到 bin 目录
set_target_properties(divider_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${LOXXCC_INSTALL_BIN_DIR}
)

enable_testing()
add_test(TEST all_test COMMOND divider_tests)
