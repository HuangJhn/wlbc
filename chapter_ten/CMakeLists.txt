
cmake_minimum_required(VERSION 3.10)

project(sctp)

add_executable(sctpserv01 sctpserv01.c)
add_executable(sctpclient01 sctpclient01.c)

add_executable(sctpclient02 sctpclient02.c)

target_link_libraries(sctpserv01 libsctp.a)
target_link_libraries(sctpclient01 libsctp.a)

target_link_libraries(sctpclient02 libsctp.a)