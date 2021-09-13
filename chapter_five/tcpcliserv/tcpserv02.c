
// linux
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>

// c std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

// macro
#define BUFFER_SIZE 1460
#define SERV_PORT   8010
#define BACKLOG     5

// daclare struct info
struct args
{
    long arg1;
    long arg2;
};

struct result
{
    long sum;
};

// typedef 
typedef struct sockaddr    SA;
typedef struct sockaddr_in SAI;

// function declare

int listen_function(int argc,char * argv[]);
void str_echo(int sockfd);


// static function

// TOTO:print protocol address and default is SAI and protocol is AF_INET
void
printProtocolAddress(SAI * address)
{
    static char buffer[16];
    bzero(buffer,sizeof(buffer));
    inet_ntop(AF_INET,&address->sin_addr,buffer,sizeof(buffer));

    uint16_t port = ntohs(address->sin_port);

    // print address info
    printf("address = %s and port = %d.\n",buffer,port);
}

void
sig_child(int signalno)
{
    int   state;
    pid_t pid;

    while((pid = waitpid(-1,&state,WNOHANG)) > 0)
    {
        printf("child process id = %d is over.\n",pid);
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
    listen_function(argc,argv);
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
        printProtocolAddress(&cliAddr);
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
    struct args structArgs;
    struct result sum;
again:
    bzero(&structArgs,sizeof(struct args));
    bzero(&sum,sizeof(struct result));
    bzero(buf,BUFFER_SIZE);

    while((n = read(sockfd,&structArgs,sizeof(struct args))) > 0)
    {
        long arg1,arg2;
        int len = 0;
        printf("recv = %ld %ld.\n",structArgs.arg1,structArgs.arg2);
        // client must keep the format send data to the server 
        // if(sscanf(buf,"%ld%ld",&arg1,&arg2) == 2)
        // {
        //     printf("%ld %ld.\n",arg1,arg2);
        //     len = snprintf(buf,sizeof(buf),"%ld",arg1 + arg2);
        // }
        // else
        // {
        //     len = snprintf(buf,sizeof(buf),"input error.\n");
        // }
        // strlen无法准确判断出buf当前写入的长度
        // n = strlen(buf);
        sum.sum = structArgs.arg1 + structArgs.arg2;
        write(sockfd,&sum,sizeof(struct result));
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

