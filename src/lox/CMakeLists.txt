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
)

add_library(loxcompile SHARED STATIC ${SOURCE_FILES})
add_executable(loxcompiler compiler.cpp)
install(TARGETS loxcompile DESTINATION ${LOXXCC_INSTALL_LIB_DIR})
install(FILES compiler.h DESTINATION ${LOXXCC_INSTALL_INCLUDE_DIR})
