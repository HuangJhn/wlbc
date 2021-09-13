// author:huangj
// 练习在服务器使用select函数

// linux
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<sys/wait.h>
#include<netinet/in.h>
#include<errno.h>

// c std
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<assert.h>

// macro
#define BUFFER_SIZE 1460    // ipv4 data packet
#define SERV_PORT   8010    // listen port
#define BACKLOG     5

// typedef
typedef struct sockaddr     SA;
typedef struct sockaddr_in  SAI;

// function declare
void str_echo();    // version 1
int listen_function(int argc,char * argv[]);

// static function declare and definition
// print peer protocol info
void printProtocolAddr(SAI * addr)
{
    uint16_t port = ntohs(addr->sin_port);
    char addrIp[16];    bzero(addrIp,16);
    inet_ntop(addr->sin_family,&addr->sin_addr,addrIp,16);

    printf("address = %s and port = %d.\n",addrIp,port);
}
// signal process function
void sig_child(int signo)
{
    pid_t pid;
    int   stat;

    while((pid = waitpid(-1,&stat,WNOHANG))>0)
    {
        printf("child %d terminated.\n",pid);
    }
    return;
}

// print error string and error code
void print(int error_code,const char * error_str)
{
    printf("error_code = %d,error content : %s.\n",error_code,error_str);
}
// main function
int
main(int argc,char * argv[])
{
    if(listen_function(argc,argv) == EXIT_FAILURE)
    {
        printf("start server failed.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int
listen_function(int argc,char * argv[])
{
    // signal(SIGCHLD,sig_child);    // no need
    int listenfd = -1,connfd = -1;
    pid_t childPid;

    socklen_t cliLen;
    SAI cliAddr,    servAddr;

    if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        printf("create socket fd failed and error code = %d\n,",errno);
        return EXIT_FAILURE;
    }
    bzero(&servAddr,sizeof(SAI));

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(SERV_PORT);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    assert(bind(listenfd,(SA*)&servAddr,sizeof(SAI))==0);

    listen(listenfd,BACKLOG);

    // connfd client array
    int connfdClient[FD_SETSIZE];
    int connfdIndex = -1;

    int maxfd = listenfd;
    // read buffer len
    ssize_t bufferLen = 0;
    // read buffer
    char    buffer[BUFFER_SIZE];

    fd_set readSet;
    fd_set allSet;

    FD_ZERO(&readSet);
    FD_ZERO(&allSet);

    // set listenfd
    FD_SET(listenfd,&allSet);
    for(int index = 0;index < FD_SETSIZE;index++)
    {
        connfdClient[index] = -1;
    }
    for(;;)
    {
        readSet = allSet;
        bzero(buffer,BUFFER_SIZE);

        int nready = select(maxfd + 1,&readSet,NULL,NULL,NULL);
        if(FD_ISSET(listenfd,&readSet))
        {
            // ready to accet a sockfd
            connfd = accept(listenfd,NULL,NULL);
            for(int index = 0;index < FD_SETSIZE;index++)
            {
                if(connfdClient[index] < 0)
                {
                    connfdClient[index] = connfd;
                    connfdIndex = index;    // record max fd of the index
                    break;
                }
            }
            if(connfdClient[connfdIndex]!=connfd)
            {
                // check has set connfdIndex and equal FD_SETSIZE size
                printf("has error happend.n");
                break;
            }
            // set current connfd
            FD_SET(connfd,&allSet);
            if(maxfd < connfd)
            {
                maxfd = connfd;
            }
            if((nready--) <= 0)
            {
                // no fd is ready to read
                continue;
            }
        }
        for(int index = 0;index <= connfdIndex;index++)
        {
            if(connfdClient[index] < 0)
            {
                continue;
            }
            if(FD_ISSET(connfdClient[index],&readSet))
            {
                if((bufferLen = read(connfdClient[index],buffer,BUFFER_SIZE)) == 0)
                {
                    // clear set and close fd and delete from connfdClient
                    FD_CLR(connfdClient[index],&allSet);
                    close(connfdClient[index]);
                    connfdClient[index] = -1;
                }
                else
                {
                    // echo buffer content
                    write(connfdClient[index],buffer,bufferLen);
                }
            }
            if((nready--) <= 0)
            {
                // no fd is ready to read
                break;
            }
        }
    }
    close(listenfd);
    return EXIT_SUCCESS;
}
