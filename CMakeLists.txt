cmake_minimum_required(VERSION 3.2)

project(loxxcpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})


# 添加 GoogleTest 子模块
add_subdirectory(extern/googletest)

set(LOXXCC_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(LOXXCC_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(LOXXCC_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(LOXXCC_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/lox)

include_directories(${LOXXCC_INSTALL_INCLUDE_DIR})
include_directories(${LOXXCC_HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)


