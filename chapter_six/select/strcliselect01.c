
// author: huangj
// practice select function 

// linux
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>

// c std
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// macro
#define SERVER_PORT 8010
#define BUFFER_SIZE 1460

// typedef
typedef struct sockaddr    SA;
typedef struct sockaddr_in SAI;

// function declare
// connect to server
void connectHelper(char * argv);
void str_cli(FILE * fp,int sockfd);
void str_cli02(FILE * fp,int sockfd);

// static function to process special 
void 
printfError(int error_code,char * str)
{
    printf("error_code = %d, error str = %s.\n",error_code,str);
}

// main function
int
main(int argc,char * argv[])
{
    if(2!=argc)
    {
        // usage();
        printf("Usage: %s <IPAddress>.\n",argv[0]);
        return EXIT_FAILURE;
    }   
    connectHelper(argv[1]);
    return EXIT_SUCCESS;
}

void 
connectHelper(char * argv)
{
    int error_code = 0;
    int sockfd;
    SAI servAddr;

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        error_code = errno;
        printfError(error_code,"create socket fd failed.\n");
        return;
    }
    bzero(&servAddr,sizeof(SAI));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port   = htons(SERVER_PORT);
    inet_pton(servAddr.sin_family,argv,&servAddr.sin_addr);

    if(connect(sockfd,(SA*)&servAddr,sizeof(SAI)) < 0)
    {
        error_code = errno;
        printfError(error_code,"connect failed.\n");
        return;
    }
    // connected

    // process data
    // str_cli(stdin,sockfd);
    FILE * makefileFp = fopen("Makefile","r");

    if(NULL != makefileFp)
    {
        printf("test-1 log.\n");
        str_cli02(makefileFp,sockfd);
    }

    close(sockfd);
}
// first version 
void
str_cli(FILE * fp,int sockfd)
{
    int error_code = 0;
    ssize_t len = 0;
    int maxfd1;
    fd_set readSet;
    char sendBuffer[BUFFER_SIZE], recvBuffer[BUFFER_SIZE];

    FD_ZERO(&readSet);
    for(;;)
    {
        {
            bzero(&sendBuffer,BUFFER_SIZE);
            bzero(&recvBuffer,BUFFER_SIZE);
        }
        FD_SET(fileno(fp),&readSet);
        FD_SET(sockfd,&readSet);

        // maxfd1 = max(fileno(fp),sockfd) + 1;
        maxfd1 = fileno(fp) > sockfd ? (fileno(fp) + 1):(sockfd + 1);
        select(maxfd1,&readSet,NULL,NULL,NULL);
        if(FD_ISSET(sockfd,&readSet))
        {
            if(len = read(sockfd,recvBuffer,BUFFER_SIZE) == 0)
            {
                error_code = errno;
                printfError(error_code,"str_cli:server terminated prematurely");
                return;
            }
            fputs(recvBuffer,stdout);
        }
        if(FD_ISSET(fileno(fp),&readSet))
        {
            if(fgets(sendBuffer,BUFFER_SIZE,fp) == NULL)
            {
                return;
            }
            // send msg
            write(sockfd,sendBuffer,strlen(sendBuffer));
        }
    }
}

void
str_cli02(FILE * fp,int sockfd)
{
    int     maxfdp1,stdineof;
    int     n;
    int     error_code = 0;
    char    buffer[BUFFER_SIZE];
    fd_set  readSet;

    stdineof = 0;
    FD_ZERO(&readSet);
    for(;;)
    {
        bzero(buffer,BUFFER_SIZE);
        n = 0;
        if(0 == stdineof)
        {
            FD_SET(fileno(fp),&readSet);
        }
        FD_SET(sockfd,&readSet);
        maxfdp1 = fileno(fp) > sockfd ? (fileno(fp) + 1) : (sockfd + 1);
        select(maxfdp1,&readSet,NULL,NULL,NULL);
        
        printf("test-2 log.\n");

        if(FD_ISSET(sockfd,&readSet))
        {
            if((n = read(sockfd,buffer,BUFFER_SIZE)) == 0)
            {
                if(1 == stdineof)
                {
                    // 读取完成
                    return; 
                }
                error_code = errno;
                printfError(error_code,"str_cli:server terminated prematurely");
                return;
            }
            // fputs(buffer);
            // write(fileno(stdout),buffer,n);
            fputs(buffer,stdout);
        }
        if(FD_ISSET(fileno(fp),&readSet))
        {
            if((n = read(fileno(fp),buffer,BUFFER_SIZE)) == 0)
            {
                stdineof = 1;
                shutdown(sockfd,SHUT_WR);   // 发FIN 关闭写的一半 还可以读数据
                FD_CLR(fileno(fp),&readSet);    // fp句柄没有数据可读
                continue;
            }
            write(sockfd,buffer,n);
        }
    }
}