cmake_minimum_required(VERSION 3.2)
project(divider_tests)

add_subdirectory(lib/googletest)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

include_directories(lib/googletest/googletest/include)
include_directories(${LOXXCC_HEADERS_DIR})
include_directories(${LOXXCC_INSTALL_INCLUDE_DIR})

set(SOURCE_FILES main.cpp 
                 src/divider_tests.cpp
                 src/scanner_tests.cpp)

add_executable(divider_tests ${SOURCE_FILES})
target_link_libraries(divider_tests gtest loxcompile)
install(TARGETS divider_tests DESTINATION bin)

configure_file(src/config.h.in ${CMAKE_SOURCE_DIR}/test/src/config.h)
