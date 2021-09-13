
#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define MAXLINE 1024

//IPV6

int time_server(int argc,char * argv[]);

int
main(int argc,char * argv[])
{
    if(time_server(argc,argv) == 1)
    {
        // return a exit_failure
        printf("has error.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
//TODO:listen 13 port and return time
int
time_server(int argc,char * argv[])
{
    int     sockfd = -1,n;
    char    recvline[MAXLINE + 1];
    struct  sockaddr_in6 servaddr;

    if(argc!=2)
    {
        printf("Usage: a.out <IPAddress>.\n");
        return EXIT_FAILURE;
    }
    if((sockfd = socket(AF_INET6,SOCK_STREAM,0)) < 0)
    {
        printf("socket error (call socket craete socket fd failed.\n)");
        return EXIT_FAILURE;
    }
    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin6_family = AF_INET6;
    servaddr.sin6_port   = htons(13);
    // servaddr.sin_addr   = htonl();
    if(inet_pton(AF_INET6,argv[1],&servaddr.sin6_addr) < 0)
    {
        printf("inet_pton error for %s.\n",argv[1]);
        return EXIT_FAILURE;
    }
    // SA stand for struct sockaddr
    if(connect(socket,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
    {
        printf("connect error.\n");
        return EXIT_FAILURE;
    }
    //read返回0(表明远端关闭连接)或负值(表示发生错误)时终止循环
    while((n = read(sockfd,recvline,MAXLINE)) > 0)
    {
        recvline[n] = 0;
        if(fputs(recvline,stdout) == EOF)
        {
            printf("fputs error.\n");
            return EXIT_FAILURE;
        }
    }
    if(n < 0)
    {
        // has error happend
        printf("read error.\n");
        return EXIT_FAILURE;
    }
    //关闭套接字
    close(sockfd);
    return EXIT_SUCCESS;
}
