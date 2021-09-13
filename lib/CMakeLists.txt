

cmake_minimum_required(VERSION 3.10)

set(CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-std=c++0x")

# include_directories("./")

add_executable(read_test read_test.cpp error.cpp read.cpp)