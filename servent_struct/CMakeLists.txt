cmake_minimum_required(VERSION 3.10)

project(servent)

file(GLOB_RECURSE source ./src/*.c)

message(${source})

add_executable(${PROJECT_NAME} ${source})

