cmake_minimum_required(VERSION 3.2)
project(loxxcpp)

add_subdirectory(lox)
add_subdirectory(vm)
set(SOURCE_FILES main.cpp)

#add_executable(loxcompiler ${SOURCE_FILES})
#target_link_libraries(divider division)
# install(TARGETS divider DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})
