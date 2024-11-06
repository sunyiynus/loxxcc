cmake_minimum_required(VERSION 3.2)
project(loxxcompiler C CXX)

set(SOURCE_FILES
    compiler.h
    compiler.cpp
    errors.cpp
    scanner.h
    scanner.cpp
    printer.h
    printer.cpp
    expression.h
    expression.cpp
    parser.h
    parser.cpp
    evaluator.h
    evaluator.cpp
    stmt.h
    stmt.cpp
)

add_library(loxcompile SHARED STATIC ${SOURCE_FILES})
add_executable(loxcompiler compiler.cpp)



# 设置目标的输出目录到 bin 目录
set_target_properties(loxcompiler PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${LOXXCC_INSTALL_BIN_DIR}
)