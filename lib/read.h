#pragma once

// linux
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>

// c std
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

// read function
size_t Read(int __fd,char * __buffer,size_t __len);

size_t Recv(int __fd,char * __buffer,size_t __len,size_t __opt);
