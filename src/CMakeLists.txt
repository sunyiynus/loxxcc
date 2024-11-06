cmake_minimum_required(VERSION 3.2)
project(loxc)

add_subdirectory(lox)
add_subdirectory(vm)
set(SOURCE_FILES main.cpp)

add_executable(loxxcc ${SOURCE_FILES})
# install(TARGETS divider DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})
# 设置目标的输出目录到 bin 目录
set_target_properties(loxxcc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${LOXXCC_INSTALL_BIN_DIR}
)