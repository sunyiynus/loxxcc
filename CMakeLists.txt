cmake_minimum_required(VERSION 3.2)

project(loxxcpp VERSION 1.1)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

# 使用 FetchContent 下载并配置 GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()




# 添加 GoogleTest 子模块
# add_subdirectory(extern/googletest)

set(LOXXCC_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/common)
set(LOXXCC_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(LOXXCC_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(LOXXCC_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/lox)
set(LOXXVM_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/vm)

include_directories(${LOXXCC_INSTALL_INCLUDE_DIR})
include_directories(${LOXXCC_HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

configure_file(src/common/config.h.in ${CMAKE_SOURCE_DIR}/test/src/jlox/config.h)

