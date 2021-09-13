
// author: huangj

// poll函数实现的echo客户端

// linux
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <poll.h>

// c std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

// macro
#define SERVER_PORT 8010
#define BUFFER_SIZE 1460
#define POLLFD_SIZE 1024

// typedef
typedef struct sockaddr     SA;
typedef struct sockaddr_in  SAI;

// function declare

void connectHelper(char * ipAddress);
void str_cli(FILE * fp,int sockfd);

// static function
void
printfError(int error_code,const char * str)
{
    printf("error_code = %d, error str = %s.\n",error_code,str);
}

// main function
int
main(int argc,char * argv[])
{
    if(2!=argc)
    {
        printfError(0,"Usage:execName <IPaddress>");
        return EXIT_FAILURE;
    }
    connectHelper(argv[1]);
    return EXIT_SUCCESS;
}

void
connectHelper(char * ipAddress)
{
    int     sockfd = -1;
    int     error_code = 0;
    SAI     serverAddress;

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        error_code = errno;
        printfError(error_code,"create socket fd failed");
        return;
    }
    bzero(&serverAddress,sizeof(SAI));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port   = htons(SERVER_PORT);
    inet_pton(serverAddress.sin_family,ipAddress,&serverAddress.sin_addr);

    if(connect(sockfd,(SA*)&serverAddress,sizeof(SAI)) < 0)
    {
        error_code = errno;
        printfError(error_code,"connect server failed");
        return;
    }
    // test std input
    // str_cli(stdin,sockfd);
    // test file input
    FILE * fp = fopen("Makefile","r");
    if(NULL != fp)
    {
        str_cli(fp,sockfd);
    }
    close(sockfd);
}
void
str_cli(FILE * fp,int sockfd)
{
    ssize_t bufferLen = 0;
    char   buffer[BUFFER_SIZE];
    struct pollfd fdfamily[2];  // fp and sockfd

    bzero(fdfamily,sizeof(fdfamily));
    bzero(buffer,sizeof(buffer));

    fdfamily[0].fd = sockfd;
    fdfamily[0].events = POLLIN;

    fdfamily[1].fd = fileno(fp);
    fdfamily[1].events = POLLIN;

    for(;;)
    {
        int numberfd = poll(fdfamily,2,-1);
        for(int index = 0;index < 2;index++)
        {
            // to zero
            bzero(buffer,BUFFER_SIZE);
            if(fdfamily[index].revents & (POLLIN | POLLERR))
            {
                if((bufferLen = read(fdfamily[index].fd,buffer,BUFFER_SIZE)) < 0)
                {
                    if(EINTR == errno)
                    {
                        continue;
                    }
                    else
                    {
                        int errorCode = errno;
                        printfError(errorCode,"read failed");
                        exit(-1);
                    }
                }
                else if(bufferLen == 0)
                {
                    // close
                    fdfamily[index].fd = -1;
                    printfError(0,"peer closed");
                }
                else
                {
                    if(fileno(fp) == fdfamily[index].fd)
                    {
                         // send message
                        write(sockfd,buffer,bufferLen);
                    }
                    else
                    {
                        printf("content = %s.\n",buffer);
                    }
                }
            }
            if(fdfamily[index].revents & POLLOUT)
            {
                // 写

            }
            fdfamily[index].revents = 0;
        }
    }
}

