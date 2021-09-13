// author: huangj

// poll函数作为的服务器示例

// linux
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <poll.h>

// c std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

// macro
#define SERVER_PORT 8010
#define BUFFER_SIZE 1460
#define POLL_SIZE   1024
#define BACKLOG     5

// 内存对齐
// #pragma pack(8)

// typedef
typedef struct sockaddr     SA;
typedef struct sockaddr_in  SAI;

// function declare
int listenFunction();
// static function
void
printfError(int error_code,const char * str)
{
    printf("error_code = %d, error str = %s.\n",error_code,str);
}
void 
printProtocolAddr(SAI * addr)
{
    uint16_t port = ntohs(addr->sin_port);
    char addrIp[16];    bzero(addrIp,16);
    inet_ntop(addr->sin_family,&addr->sin_addr,addrIp,16);

    printf("address = %s and port = %d.\n",addrIp,port);
}
// main function
int
main(int argc,char * argv[])
{
    // if(2!=argc)
    {
        // printfError(0,"Usage:execName <IPaddress>");
        // return EXIT_FAILURE;
    }
    listenFunction();
    return EXIT_SUCCESS;
}
int
listenFunction()
{
    int     listenfd,   connfd;
    int     errorCode = 0;
    SAI     serverAddress;

    if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        errorCode = errno;
        printfError(errorCode,"create socket fd failed.");
        return EXIT_FAILURE;
    }
    bzero(&serverAddress,sizeof(SAI));

    serverAddress.sin_family     = AF_INET;
    serverAddress.sin_port       = htons(SERVER_PORT);
    serverAddress.sin_addr.s_addr= htonl(INADDR_ANY);

    assert(bind(listenfd,(SA*)&serverAddress,sizeof(SAI))==0);

    listen(listenfd,BACKLOG);

    // buffer
    char    buffer[BUFFER_SIZE];
    ssize_t bufferLen = 0;  

    // poll 
    struct pollfd client[POLL_SIZE];

    client[0].fd = listenfd;
    // could accept and POLLIN or POLLRDNORM
    client[0].events = POLLRDNORM;  
    for(int index = 1;index < POLL_SIZE;index++)
    {
        client[index].fd = -1;
    }
    long int maxi = 0;
    for(;;)
    {
        // alwayly blocked
        int numberfd = poll(client,maxi+1,-1);
        // pri process listenfd
        if(client[0].revents & POLLRDNORM)
        {
            connfd = accept(client[0].fd,NULL,NULL);

            for(int index = 0;index < POLL_SIZE;index++)
            {
                if(client[index].fd < 0)
                {
                    client[index].fd = connfd;
                    maxi = index;
                    break;
                }
            }
            if(client[maxi].fd != connfd)
            {
                printfError(1,"over POLL_SIZE");
                exit(-1);
            }
            client[maxi].events = POLLRDNORM;

            if((numberfd--) <= 0)
            {
                // no need fd
                continue;
            }
        }
        for(int index = 1;index <= maxi;index++)
        {
            bzero(buffer,BUFFER_SIZE);
            if((connfd = client[index].fd) < 0)
            {
                continue;
            }
            if(client[index].revents & (POLLRDNORM | POLLERR))
            {
                if((bufferLen = read(connfd,buffer,BUFFER_SIZE)) < 0)
                {
                    // RST
                    if(errno == ECONNRESET)
                    {
                        close(connfd);
                        client[index].fd = -1;
                    }
                    else
                    {
                        printfError(1,"read error");
                        exit(-1);
                    }
                }
                else if(0 == bufferLen)
                {
                    errorCode = errno;
                    printfError(errorCode,"peer is closed");
                    // close connfd and delete fd
                    client[index].fd      = -1;
                    client[index].events  = 0;
                    client[index].revents = 0;
                    close(connfd);
                }
                else
                {
                    // echo
                    write(connfd,buffer,bufferLen);
                }
            }
            if((numberfd--) <= 0)
            {
                break;
            }
        }
    }
}