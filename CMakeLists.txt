cmake_minimum_required(VERSION 3.8)

project(JaFilesystem CXX)

option(BUILD_TESTS "Turn on to build tests" ON)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(${CMAKE_SOURCE_DIR}/Catch2)
    add_subdirectory(test)
endif(BUILD_TESTS)
