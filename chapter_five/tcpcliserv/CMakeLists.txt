

cmake_minimum_required(VERSION 3.10)

project(echo_server_and_client)

set(COMPILE_FLAGS "-Wall -Wshadow -Wunused")

add_executable(tcpserv01 tcpserv01.c)
add_executable(tcpserv02 tcpserv02.c)

add_executable(tcpcli01 tcpcli01.c)
add_executable(tcpcli02 tcpcli02.c)

target_link_libraries(tcpserv01 PUBLIC pthread.so)
target_link_libraries(tcpserv02 PUBLIC pthread.so)

target_link_libraries(tcpcli01 PUBLIC pthread.so)
target_link_libraries(tcpcli02 PUBLIC pthread.so)
