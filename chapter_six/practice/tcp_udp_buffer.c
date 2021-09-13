
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

// function declare
void tcpBuffer();
void udpBuffer();

///////////////////////////////////////////////////////////////////////////
// tcp send buffer size = 16384.
// tcp rcv buffer size = 131072.
// ——————————————————————————————————————————————
// udp send buffer size = 212992.
// udp rcv buffer size = 212992.

// linux info:Linux iZbp12ibqc0f9rucd631pmZ 4.15.0-144-generic #148-Ubuntu SMP Sat May 8 02:33:43 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux

///////////////////////////////////////////////////////////////////////////

// main function
int
main(int argc,char * argv[])
{
    
    tcpBuffer();
    printf("——————————————————————————————————————————————\n");
    udpBuffer();
    return EXIT_SUCCESS;
}
void
tcpBuffer()
{
    int sockfd = -1;

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        printf("create socket fd failed.\n");
        return;
    }
    long sndLen = 0;
    socklen_t len = sizeof(sndLen);
    getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&sndLen,&len);

    // listen(sockfd,5);

    printf("tcp send buffer size = %ld.\n",sndLen);

    long rcvLen = 0;
    getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&rcvLen,&len);

    printf("tcp rcv buffer size = %ld.\n",rcvLen);

    close(sockfd);
}

void
udpBuffer()
{
    int sockfd = -1;

    if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
    {
        printf("create socket fd failed.\n");
        return;
    }
    long sndLen = 0;
    socklen_t len = sizeof(sndLen);
    getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&sndLen,&len);

    printf("udp send buffer size = %ld.\n",sndLen);

    long rcvLen = 0;
    getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&rcvLen,&len);

    printf("udp rcv buffer size = %ld.\n",rcvLen);

    close(sockfd);
}