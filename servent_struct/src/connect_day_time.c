/**
 * @file connect_day_time.cpp
 * @author huangj (1435054809@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <netdb.h> // for gethostbyname
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 40000

typedef struct sockaddr SA;
typedef struct sockaddr_in SAI;

/**
 * @brief 
 * 
 * @param argc 表示argv数组的长度
 * @param argv 
 */
void flow(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("需要命令行参数\n");
        return;
    }

    const char *hostName = argv[1];   // 拿到的这个值可能是域名、主机名、或者是ip地址。
    const char *serverName = argv[2]; // 服务名称---需要是在协议标识的服务名称

    // 主机信息
    struct hostent *sh;
    struct in_addr **ppAddress;
    if ((sh = gethostbyname(hostName)) == NULL)
    {
        // 检查是否为IP地址
        // 没有获取到对应主机的IP信息 ｜ 直接将hostName作为一个IP地址
        // inet_pton(AF_INET,);
        return;
    }
    else
    {
        // 读取IP地址
        ppAddress = (struct in_addr **)(sh->h_addr_list);
    }

    struct servent *serviceInfo;
    // 读取服务信息 --
    if ((serviceInfo = getservbyname(serverName, NULL)) == NULL)
    {
        // 读取服务失败
        return;
    }
    int sockfd = 0;
    SAI serverAddress;
    if ((sockfd = socket(sh->h_addrtype, SOCK_STREAM, 0)) < 0)
    {
        // 创建文件socket文件描述符失败
        return;
    }
    for (; *ppAddress != NULL; ppAddress++)
    {
        serverAddress.sin_family = sh->h_addrtype;
        serverAddress.sin_addr = *(*ppAddress);
        serverAddress.sin_port = serviceInfo->s_port;

        if(connect(sockfd,(SA*)&serverAddress,sizeof(serverAddress)) < 0)
        {
            printf("connect error and error_code : %d.\n",errno);
            continue;
        }
        // 连接成功
        printf("connected the server : %s.\n",serviceInfo->s_name);
        break;
    }
    // 连接上服务需要做特殊的处理
    // 下面是连接www.baidu.com https 服务
    {
        // char const * req = "GET / HTTP/1.1\r\nUser-Agent: chrome/7.58.0\r\nAccept: */*\r\n\r\n";
        char request[1000];
        bzero(request,1000);
        snprintf(request,1000,"GET / HTTP/1.1\r\nUser-Agent: chrome/7.58.0\r\nAccept: */*\r\n\r\n");
        // "GET / HTTP/1.1\r\nHost: www.baidu.com\r\n\r\n";
        // no use
        // const char * req = "GET / HTTP/1.1\nHost: www.baidu.com\nConnection: keep-alive\rContent-Type: text/html;charset=utf-8\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36\r\n";
        // const char * req = "GET / HTTP/1.1\n    \
        // Accept: */*\r\n";
        // const char * req = 
        // "GET /index HTTP/1.1\r\n    \
        // user-agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36\r\n \
        // Connection: keep-alive\r\n\r\n";

        printf("%s.\n",request);

        send(sockfd,request,strlen(request),0);

        struct timeval time = {3,0};
        // setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&time,sizeof(time));

        char buffer[BUFFER_SIZE];
        bzero(buffer,BUFFER_SIZE);
        recv(sockfd,buffer,BUFFER_SIZE,0);
        // printf("%ld.\n",recv(sockfd,buffer,BUFFER_SIZE,0));
        // printf("content : %s .\n",buffer);
        printf("error_code = %d.\n",errno);

        write(fileno(stdout),buffer,strlen(buffer));

    }
    return;
}