

cmake_minimum_required(VERSION 3.10)

project(select)

set(CMAKE_CXX_EXTENSIONS "-Wall -Wunused -Wshadow")
set(CMAKE_CXX_FLAGS -Wall -Wunused -Wshadow)

add_executable(tcpclipoll01 tcpclipoll01.c)
add_executable(tcpservpoll01 tcpservpoll01.c)