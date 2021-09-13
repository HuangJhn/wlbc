
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/time.h>
#include<unistd.h>
#include<errno.h>

#include<arpa/inet.h>
#include<sys/socket.h>

// use local ip 127.0.0.1:13

#define MAXLINE 1024

int time_server(int argc,char * argv[]);

void socket_info();

int
main(int argc,char * argv[])
{
    socket_info();
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
    struct  sockaddr_in servaddr;

    if(argc!=2)
    {
        printf("Usage: a.out <IPAddress>.\n");
        return EXIT_FAILURE;
    }
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) <= 0)
    // if((sockfd = socket(9999,SOCK_STREAM,0)) <= 0)  // Address family not supported by protocol
    {
        printf("socket error (call socket craete socket fd failed),error code = %d.\n",errno);
        return EXIT_FAILURE;
    }
    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(13);
    // servaddr.sin_port   = htons(9999);

    // servaddr.sin_addr   = htonl();
    if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr) < 0)
    {
        printf("inet_pton error for %s.\n",argv[1]);
        return EXIT_FAILURE;
    }
    // SA stand for struct sockaddr
    if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
    {
        printf("connect error code = %d.\n",errno);
        return EXIT_FAILURE;
    }
    //TODO:练习:增加一个计数器，来查看这个read循环有多少次大于0。
    size_t count = 0;
    //read返回0(表明远端关闭连接)或负值(表示发生错误)时终止循环
    while((n = read(sockfd,recvline,MAXLINE)) > 0)
    {
        // printf("n = %d.\n",n);   // 27
        // printf("strlen(recline) = %lu.\n",strlen(recvline)); // 26    if the server no include '\0' maybe > 26
        count = count + 1;  
        recvline[n] = 0;    // '\0'
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
    printf("count = %lu.\n",count); // print count = 1
    //关闭套接字
    close(sockfd);
    return EXIT_SUCCESS;
}

void 
socket_info()
{
    struct sockaddr sa;
    struct sockaddr_in sai;
    int socket = 0;

    bzero(&sa,sizeof(sa));
    bzero(&sai,sizeof(sai));

    printf("sizeof(struct sockaddr) = (%lu).\n",sizeof(sa));
        printf("\t\tsizeof(sa.sa_data) = %lu.\n",sizeof(sa.sa_data));
        printf("\t\tsizeof(sa.sa_family) = %lu.\n",sizeof(sa.sa_family));

    printf("sizeof(struct sockadde_in) = (%lu).\n",sizeof(struct sockaddr_in));
        printf("\t\tsizeof(sai.sin_family) = %lu.\n",sizeof(sai.sin_family));
        printf("\t\tsizeof(sai.sin_addr) = %lu.\n",sizeof(sai.sin_addr));
        printf("\t\tsizeof(sai.sin_port) = %lu.\n",sizeof(sai.sin_port));
        printf("\t\tsizeof(sai.sin_zero) = %lu.\n",sizeof(sai.sin_zero));

    printf("sizeof(socket) = sizeof(%lu).\n",sizeof(socket));
}
 