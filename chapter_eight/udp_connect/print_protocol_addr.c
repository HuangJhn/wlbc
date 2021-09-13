

// linux 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>

// c std
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// macro
#define SERV_PORT   8010

// typedef 
typedef struct sockaddr     SA;
typedef struct sockaddr_in  SAI;

// declare function
void udp_connect(char * addr);
void printfAddr(SAI * addr);

// static function
void printfAddr(SAI * addr)
{
    static char buffer[16];
    bzero(buffer,sizeof(buffer));
    inet_ntop(addr->sin_family,&addr->sin_addr,buffer,sizeof(buffer));
    printf("addr = %s,port = %d.\n",buffer,ntohs(addr->sin_port));
}

// main function
int
main(int argc,char * argv[])
{
    if (argc != 2)
    {
        printf("Usage:%s <IPaddress>.\n",argv[0]);
        return EXIT_FAILURE;
    }
    udp_connect(argv[1]);
    return EXIT_SUCCESS;
}
void
udp_connect(char * addr)
{
    int         sockfd;
    socklen_t   len;
    SAI         cliaddr,    servaddr;

    // use udp protocol
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd < 0)
    {
        printf("create sockfd failed.\n");
        return;
    } 
    bzero(&cliaddr,sizeof(cliaddr));
    bzero(&servaddr,sizeof(servaddr));
    // connect();

    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(SERV_PORT);
    inet_pton(AF_INET,addr,&servaddr.sin_addr);

    connect(sockfd,(SA*)&servaddr,sizeof(servaddr));

    len = sizeof(cliaddr);
    getsockname(sockfd,(SA*)&cliaddr,&len);

    printfAddr(&cliaddr);
}
