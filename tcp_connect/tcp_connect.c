
// linux
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

// c std
#include <string.h>

// com
// gcc -Wall -Wunused tcp_connect.c -c

/**
 * @brief 根据域名(主机名/IP地址)-host_name 连接serivce_name服务
 * 
 * @param host_name 
 * @param serivce_name 
 * @return int 
 */
int tcp_connect(const char * host_name,const char * serivce_name)
{
    struct addrinfo hints;
    struct addrinfo *result;
    bzero(&hints,sizeof(hints));

    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if(getaddrinfo(host_name,serivce_name,&hints,&result) != 0)
    {
        // 调用函数出错
        return -1;
    }
    // link list
    struct addrinfo * tmp = result;
    int sockfd = 0;
    do
    {   
        sockfd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
        if(sockfd < 0)
        {
            continue;
        }
        // connect
        if(connect(sockfd,(struct sockaddr *)&tmp->ai_addr,tmp->ai_addrlen) == 0)
        {
            break;
        }        
    } while ((tmp = tmp->ai_next)!=NULL);
    // 释放内存
    freeaddrinfo(result);
    // 连接失败了
    if(tmp == NULL)
    {
        return -1;
    }
    return sockfd;
}