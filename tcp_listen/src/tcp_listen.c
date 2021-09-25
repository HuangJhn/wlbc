/**
 * @file tcp_listen.c
 * @author huangj (1435054809@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-25
 * 
 * 
 */

#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define BACKLOG 5

typedef struct sockaddr     SA;
typedef struct sockaddr_in  SAI;

/**
 * @brief 监听套接字
 * 
 * @param host_name 
 * @param server_name 
 * @param addrlenp 
 * @return int 
 */
int tcp_listen(const char * host_name,const char * server_name,socklen_t * addrlenp)
{
    // 第一步:
    //  设置目标信息参数（筛选过滤的作用）主机信息
    // 第二步:
    //  根据host_name和server_name获取主机信息
    // 第三步:
    //  根据获取到的主机信息，创建sock套接字，并绑定套接字地址，然后开始监听端口
    // 第四步:
    //  退出对主机信息的循环并返回sock套接字
    int     listenfd = 0,   n = 0;
    const   int on = 1;

    struct addrinfo hints;
    struct addrinfo *result = NULL;
    bzero(&hints,sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;    // ipv4 and ipv6
    hints.ai_flags    = AI_PASSIVE;     // 被动打开（被动连接）

    if (getaddrinfo(host_name,server_name,&hints,&result) != 0)
    {
        // return -1 stand for failed 
        return -1;
    }
    // iterator the host info
    struct addrinfo * tmp = result;
    while (tmp != NULL)
    {
        listenfd = socket(tmp->ai_family,tmp->ai_socktype,tmp->ai_protocol);
        if(listenfd >= 0)
        {
            // set socket option
            setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
            // bind sockfd and addr info
            assert(bind(listenfd,(SA*)tmp->ai_addr,tmp->ai_addrlen) == 0);
            // listen sock 
            listen(listenfd,BACKLOG);

            // 设置另外返回值 并 避免传递NULL导致程序崩溃
            if(addrlenp)
            {
                *addrlenp = tmp->ai_addrlen;
            }
            break;
        }
        // next host info
        tmp = tmp->ai_next;
    }
    if (tmp == NULL)
    {
        listenfd = -1;
    }
    // free memory
    freeaddrinfo(result);
    return listenfd;
}