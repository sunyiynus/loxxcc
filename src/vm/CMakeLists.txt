cmake_minimum_required(VERSION 3.2)
project(loxxcompiler C CXX)

set(SOURCE_FILES
    vm.h
    vm.cpp
)

add_library(vm SHARED STATIC ${SOURCE_FILES})
add_executable(vmrun vm.cpp)

install(TARGETS vm DESTINATION ${LOXXCC_INSTALL_LIB_DIR})
install(FILES vm.h DESTINATION ${LOXXCC_INSTALL_INCLUDE_DIR})
