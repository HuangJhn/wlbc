cmake_minimum_required(VERSION 3.10)

project(hostent)

file(GLOB_RECURSE source ./src/*.cpp)

message(${source})

add_executable(${PROJECT_NAME} ${source})

