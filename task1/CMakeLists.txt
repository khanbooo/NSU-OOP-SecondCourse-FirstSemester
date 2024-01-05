cmake_minimum_required(VERSION 3.26)
project(task1)

set(CMAKE_CXX_STANDARD 17)

add_executable(task1
        BitArray.cpp
        BitArray.h
        BitArrayException.cpp
        Google_Tests/bitarray_tests.cpp
)
