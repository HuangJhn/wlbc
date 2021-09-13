

#ifndef SOCK_H_
#define SOCK_H_

#include<sys/socket.h>
#include<arpa/inet.h>
#include<errno.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

// need check input arg

//将通配地址与一个临时端口捆绑到一个套接字
int
sock_bind_wild(int sockfd,int family)
{
    //according to family
}

//比较两个套接字地址结构的地址部分
int
sock_cmp_addr(const struct sockaddr * sockaddr1,const struct sockaddr * sockaddr2,socklen_t addrlen)
{
    enum ADDRTYPE
    {
        INET_IPV4 = 0,
        INET_IPV6 = 1
    };
    ADDRTYPE type;
    switch (addrlen)
    {
    case INET_ADDRSTRLEN:
        
        type = INET_IPV4;
        //struct sockaddr is struct sockadr_in
        break;

    default:
        break;
    }

    //TODO:需要依据type的值来进行转换

    const struct sockaddr_in * p1 = (const struct sockaddr_in*)sockaddr1;
    const struct sockaddr_in * p2 = (const struct sockaddr_in*)sockaddr2;

    if(p1->sin_addr.s_addr == p2->sin_addr.s_addr)
    {
        return 0;
    }
    else if(p1->sin_addr.s_addr > p2->sin_addr.s_addr)
    {
        return 1;
    }
    else
    {
        return -1;
    }
    return -1;
}

// 比较两个套接字地址结构的端口号部分
int
sock_cmp_port(const struct sockaddr * sockaddr1,const struct sockaddr * sockaddr2,socklen_t addrlen)
{
    switch(addrlen)
    {
        case INET_ADDRSTRLEN:
        {
            const struct sockaddr_in * p1 = (const struct sockaddr_in*)sockaddr1;
            const struct sockaddr_in * p2 = (const struct sockaddr_in*)sockaddr2;

            if(p1->sin_port == p2->sin_port)
            {
                return 0;
            }
            else if(p1->sin_port > p2->sin_port)
            {
                return 1;
            }
            else
            {
                return -1;
            }
            break;
        }
    }
    return -1;
}

//只返回端口号
int
sock_get_port(const struct sockaddr * sockaddr,socklen_t addrlen)
{
    switch(addrlen)
    {
        case INET_ADDRSTRLEN:
        {
            const struct sockaddr_in * p = (const struct sockaddr_in*)sockaddr;
            uint16_t port = ntohs(p->sin_port);
            //需要检查一下大小
            if(port > 0)
            {
                return port;
            }
            break;
        }
    }
    return -1;
}

//把一个套接字地址结构中的主机部分转换成表达式(不包括端口号)
char *
sock_ntop_host(const struct sockaddr * sockaddr,socklen_t addrlen)
{
    switch(addrlen)
    {
        case INET_ADDRSTRLEN:
        {
            const struct sockaddr_in * p = (const struct sockaddr_in*)sockaddr;
            static char * temp;//[INET_ADDRSTRLEN];
            // bzero(temp,INET_ADDRSTRLEN);
            // no repeat 不可冲重入函数
            temp = inet_ntoa(p->sin_addr);

            return temp;
            break;
        }
    }
    return NULL;
}
//把一个套接字地址结构中的地址部分置为ptr指针所指的值
void
sock_set_addr(struct sockaddr * sockaddr,socklen_t socklen,void * ptr)
{
    // check argc
    if(NULL == sockaddr)
    {
        return;
    }
    switch(socklen)
    {
        case INET_ADDRSTRLEN:
        {
            struct sockaddr_in * p = (struct sockaddr_in*)sockaddr;

            p->sin_addr = *(in_addr*)ptr;
            break;
        }
        case INET6_ADDRSTRLEN:
        {
            struct sockaddr_in6 * p = (struct sockaddr_in6*)sockaddr;

            p->sin6_addr = *(in6_addr*)ptr;

            break;
        }
    }
}

//替换套接字中的port值
void
sock_set_port(struct sockaddr * sockaddr,socklen_t socklen,int port)
{
    if(NULL == sockaddr)
    {
        return;
    }
    switch(socklen)
    {
        case INET_ADDRSTRLEN:
        {
            struct sockaddr_in * p = (struct sockaddr_in*)sockaddr;
            if(p)
            {
                p->sin_port = htons(port);
            }
            break;
        }
        case INET6_ADDRSTRLEN:
        {
            struct sockaddr_in6 * p = (struct sockaddr_in6*)sockaddr;
            if(p)
            {
                p->sin6_port = htons(port);
            }
            break;
        }
    }
}

//将套接字的地址部分设置成为通配符

void
sock_set_wild(struct sockaddr * sockaddr,socklen_t socklen)
{
    if(NULL == sockaddr)
    {
        return;
    }
    switch(socklen)
    {
        case INET_ADDRSTRLEN:
        {
            struct sockaddr_in * p = (struct sockaddr_in *)sockaddr;

            p->sin_addr.s_addr = htonl(INADDR_ANY);
            break;
        }
        case INET6_ADDRSTRLEN:
        {
            struct sockaddr_in6 * p = (struct sockaddr_in6*)sockaddr;
            //p->sin6_addr.__in6_u = htonl(IN6ADDR_ANY_INIT);
            //这里可能有问题
            p->sin6_addr = IN6ADDR_ANY_INIT;
            break;
        }
    }
}

#endif //!SOCK_H_