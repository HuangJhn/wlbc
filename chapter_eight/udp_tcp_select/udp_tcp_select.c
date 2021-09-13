
// linux
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>

// c std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#define SERVER_PORT   8010
#define BUFFER_SIZE   1460
#define BACKLOG       5

// typedef 
typedef struct sockaddr     SA;
typedef struct sockaddr_in  SAI;

// declare function

void select_tcp_udp();

// static function

void 
printfAddr(SAI * addr)
{
    static char buffer[16];
    bzero(buffer,sizeof(buffer));
    inet_ntop(addr->sin_family,&addr->sin_addr,buffer,sizeof(buffer));
    printf("addr = %s,port = %d.\n",buffer,ntohs(addr->sin_port));
}
// print error message
void 
printErrorMsg(int error_code,const char * msg)
{
    printf("error_code = %d and msg = %s.\n",error_code,msg);
}
// main function
int
main(int argc,char * argv[])
{
    select_tcp_udp();
    return EXIT_SUCCESS;
}

void
select_tcp_udp()
{
    int     listenfd,   connfd,     udpfd;
    int     error_code;
    SAI     servAddr,   cliAddr;
    socklen_t   len;

    // tcp
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    if(listenfd < 0)
    {
        error_code = errno;
        printErrorMsg(error_code,"create tcp socket fd failed");
        return;
    }
    bzero(&servAddr,sizeof(servAddr));
    bzero(&cliAddr,sizeof(cliAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_port   = htons(SERVER_PORT);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    {
        int reuseaddr = 1;
        setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&reuseaddr,sizeof(reuseaddr));
    }    
    assert(bind(listenfd,(SA*)&servAddr,sizeof(servAddr)) == 0);

    listen(listenfd,BACKLOG);

    // must - 这里必须重复设置一次。
    bzero(&servAddr,sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port   = htons(SERVER_PORT);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    udpfd = socket(AF_INET,SOCK_DGRAM,0);
    if(udpfd < 0)
    {
        error_code = errno;
        printErrorMsg(error_code,"create udp socket fd failed.\n");
        return;
    }
    assert(bind(udpfd,(SA*)&servAddr,sizeof(servAddr)) == 0);

    fd_set readset;
    FD_ZERO(&readset);

    char buffer[BUFFER_SIZE];
    int nready = 0;

    for( ; ; )
    {
        bzero(buffer,BUFFER_SIZE);

        FD_SET(listenfd,&readset);
        FD_SET(udpfd,&readset);

        nready = 0;
        nready = select(udpfd > listenfd ? udpfd + 1:listenfd + 1,&readset,NULL,NULL,NULL);

        if(FD_ISSET(listenfd,&readset))
        {
            connfd = accept(listenfd,NULL,NULL);
            if((nready = read(connfd,buffer,BUFFER_SIZE)) < 0)
            {
                // need process error
                if(errno == EINTR)
                {
                    continue;
                }
                else
                {
                    error_code = errno;
                    printErrorMsg(error_code,"msg");
                }
            }
            else if(nready == 0)
            {   
                // peer closed
                close(connfd);
            }
            else
            {
                // print
                // printf("tcp connfd recv msg = %s.\n",buffer);
                write(connfd,buffer,nready);
                close(connfd);
                bzero(buffer,BUFFER_SIZE);
            }
        }
        if(FD_ISSET(udpfd,&readset))
        {
            len = sizeof(cliAddr);
            ssize_t n = recvfrom(udpfd,buffer,BUFFER_SIZE,0,(SA*)&cliAddr,&len);

            sendto(udpfd,buffer,n,0,(SA*)&cliAddr,len);
        }
    }

}
