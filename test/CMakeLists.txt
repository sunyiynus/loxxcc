cmake_minimum_required(VERSION 3.2)
project(divider_tests)

# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

include_directories(${LOXXCC_HEADERS_DIR})
include_directories(${LOXXCC_INSTALL_INCLUDE_DIR})

set(SOURCE_FILES main.cpp 
                 src/divider_tests.cpp
                 src/expression_tests.cpp
                 src/evaluator_tests.cpp
                 src/parser_tests.cpp
                 src/variant_tests.cpp
                 src/scanner_tests.cpp)

add_executable(divider_tests ${SOURCE_FILES})
target_link_libraries(divider_tests gtest loxcompile)
# target_include_directories(divider_tests PRIVATE
#     ${CMAKE_SOURCE_DIR}/extern/googletest/googletest/include
# )

# 设置目标的输出目录到 bin 目录
set_target_properties(divider_tests PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${LOXXCC_INSTALL_BIN_DIR}
)
add_executable(debug_tests main.cpp src/debug_tests.cpp)
target_link_libraries(debug_tests gtest loxcompile)
# 设置目标的输出目录到 bin 目录
set_target_properties(debug_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${LOXXCC_INSTALL_BIN_DIR}
)

enable_testing()
add_test(NAME LoxxccTest COMMAND divider_tests)

# 指定要清理 .dot 文件的目录
set(DOT_FILE_DIR "${CMAKE_SOURCE_DIR}/bin/dot")

# 自定义命令：清理 .dot 文件
add_custom_target(clean_dot_files
    COMMAND ${CMAKE_COMMAND} -E echo "Cleaning up .dot files in ${DOT_FILE_DIR}"
    # COMMAND ${CMAKE_COMMAND} -E glob DOT_FILES ${DOT_FILE_DIR}/*.dot
    COMMAND ${CMAKE_COMMAND} -E rm -f ${DOT_FILE_DIR}/*.dot
    COMMAND ${CMAKE_COMMAND} -E rm -f ${DOT_FILE_DIR}/*.png
    COMMENT "Removing all .dot files in the directory"
)


# 自定义目标：运行所有测试
add_custom_target(run_tests_impl
    DEPENDS clean_dot_files  # 确保在运行测试之前清理 .dot 文件
    COMMAND ${CMAKE_CTEST_COMMAND}
    COMMENT "Running all tests"
)
    
add_custom_target(render_dot_files
    DEPENDS run_tests_impl  # 确保在运行测试之前清理 .dot 文件
    COMMAND ${CMAKE_COMMAND} -E env python3 ${CMAKE_SOURCE_DIR}/scripts/render_ast.py ${CMAKE_SOURCE_DIR}/bin/dot
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Rendering all .dot files to .png"
)

# 设置总执行目标
add_custom_target(test_all
    DEPENDS render_dot_files
    COMMENT "Running tests and rendering DOT files"
)

