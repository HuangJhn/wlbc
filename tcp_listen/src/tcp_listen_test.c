/**
 * @file tcp_listen_test.c
 * @author huangj (1435054809@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-25
 * 
 * 
 */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief 测试函数
 * 
 */
void ipv4_test()
{
    int sockfd = tcp_listen("0.0.0.0","daytime",NULL);
    if(sockfd < 0)
    {
        printf("listend failed.\n");
    }
    else
    {
        printf("listen success.\n");
    }
    close(sockfd);
}
/**
 * @brief 测试函数
 * 
 */
void ipv6_test()
{
    int sockfd = tcp_listen("0::0","daytime",NULL);
    if(sockfd < 0)
    {
        printf("listend failed.\n");
    }
    else
    {
        printf("listen success.\n");
    }
    accept(sockfd,NULL,NULL);
    close(sockfd);
}

int main(int argc,char * argv[])
{
    ipv6_test();
    // ipv4_test();
    return EXIT_SUCCESS;
}