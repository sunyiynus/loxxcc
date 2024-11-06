cmake_minimum_required(VERSION 3.2)
project(loxxcompiler C CXX)

set(SOURCE_FILES
    vm.h
    vm.cpp
)

add_library(vm SHARED STATIC ${SOURCE_FILES})
add_executable(vmrun vm.cpp)

# 设置目标的输出目录到 bin 目录
set_target_properties(vmrun PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${LOXXCC_INSTALL_BIN_DIR}
)