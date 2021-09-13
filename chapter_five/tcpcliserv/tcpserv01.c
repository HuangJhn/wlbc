// author:huangjie
// 测试利用tcp传输二进制数据
// 并输出返回的值

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
    signal(SIGCHLD,sig_child);
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

    for(; ;)
    {
        bzero(&cliAddr,sizeof(SAI));
        cliLen = sizeof(SAI);
        connfd = accept(listenfd,(SA*)&cliAddr,&cliLen);
        if(connfd < 0)
        {
            if(errno == EINTR)
            {
                print(4,"eintr error happend due to child signal function");
                continue;
            }
            else
            {
                int error_code = errno;
                print(error_code,"get error on accept function");
                break;
            }
        }
        if((childPid = fork()) == 0)
        {
            // exec child process
            close(listenfd);
            str_echo(connfd);
            close(connfd);
            exit(0);
        }
        printProtocolAddr(&cliAddr);
        close(connfd);
    }
    close(listenfd);
    return EXIT_SUCCESS;
}

void
str_echo(int sockfd)
{
    ssize_t n;
    char buf[BUFFER_SIZE];
again:
    bzero(buf,BUFFER_SIZE);
    while((n = read(sockfd,buf,BUFFER_SIZE)) > 0)
    {
        write(sockfd,buf,n);
    }
    if(n < 0 && errno == EINTR)
    {
        goto again;
    }
    else if(n < 0)
    {
        printf("str echo: read error and error code = %d\n",errno);
    }
}

