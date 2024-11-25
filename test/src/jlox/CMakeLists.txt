project(jlox_unittests)

include_directories(${LOXXCC_HEADERS_DIR})
include_directories(${LOXXCC_INSTALL_INCLUDE_DIR})

# 指定源文件所在的目录
set(TEST_SOURCE_DIR ${CMAKE_SOURCE_DIR}/test/src/jlox)
message(${TEST_SOURCE_DIR})
# 自动收集 src 目录下所有的 .cpp 文件
file(GLOB SOURCES ${TEST_SOURCE_DIR}/*.cpp)

add_executable(jlox_utests ${SOURCES})
target_link_libraries(jlox_utests gtest_main loxcompile )


# 设置目标的输出目录到 bin 目录
set_target_properties(jlox_utests PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${LOXXCC_INSTALL_BIN_DIR}
)
add_executable(debug_tests debug_tests.cpp)
target_link_libraries(debug_tests gtest_main loxcompile)
# 设置目标的输出目录到 bin 目录
set_target_properties(debug_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${LOXXCC_INSTALL_BIN_DIR}
)

enable_testing()
add_test(NAME LoxxccTest COMMAND jlox_utests)

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
