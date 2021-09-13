// author: huangjie

// linux
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// c std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// macro
#define SERVER_PORT 8010

// typedef 
typedef struct sockaddr     SA;
typedef struct sockaddr_in  SAI;

// function declare
void snd_rcv_buffer(int sockfd);
void connectHelper(char * ip);

//////////////////////////////////////////////////////////////////////////////////////
// snd buffer = 16384 and rcv buffer = 32768.
// snd buffer = 2626560 and rcv buffer = 32768.
//////////////////////////////////////////////////////////////////////////////////////

// main function
int
main(int argc,char * argv[])
{
    if(2 != argc)
    {
        printf("Usage: %s <IPAddress>.\n",argv[0]);
        return EXIT_FAILURE;
    }
    connectHelper(argv[1]);
    return EXIT_SUCCESS;
}
void
connectHelper(char * ip)
{
    int     sockfd = -1;
    SAI     servAddr;

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        printf("create socket failed.\n");
        return;
    }
    bzero(&servAddr,sizeof(SAI));

    servAddr.sin_family = AF_INET;
    servAddr.sin_port   = htons(SERVER_PORT);
    inet_pton(AF_INET,ip,&servAddr.sin_addr);

    // get snd and rcv buffer 
    snd_rcv_buffer(sockfd);

    if(connect(sockfd,(SA*)&servAddr,sizeof(SAI)) == -1)
    {
        printf("connect failed.\n");
        return;
    }
    snd_rcv_buffer(sockfd);

    close(sockfd);
}

void 
snd_rcv_buffer(int sockfd)
{
    long sndLen = 0;
    socklen_t len = sizeof(sndLen);
    getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&sndLen,&len);

    long rcvlen = 0;
    getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&rcvlen,&len);

    printf("snd buffer = %ld and rcv buffer = %ld.\n",sndLen,rcvlen/4);
}