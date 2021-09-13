
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "read.h"

// macro
#define BUFFER_SIZE 1460

size_t read_test_func()
{
    static char bufffer[BUFFER_SIZE];
    FILE * fd = fopen("./../error.c","rw");
    if(NULL == fd)
    {
        return 0;
    }
    return Read(fileno(fd),bufffer,BUFFER_SIZE);
}

TEST_CASE("read file","read function args is fd,buffer,len")
{
    CHECK(read_test_func() > 0);
}
TEST_CASE("read file input file name","read function args is fd,buffer,len")
{

}
