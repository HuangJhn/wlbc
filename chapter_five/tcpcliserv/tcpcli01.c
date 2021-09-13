// linux
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/time.h>
#include<errno.h>

// c std
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<assert.h>

// macro
#define SERV_PORT    8010
#define BUFFER_SIZE  1460

// typedef 
typedef struct sockaddr    SA;
typedef struct sockaddr_in SAI;

// function declare

void str_cli(FILE * fp,int sockfd);
int connectToServer(int argc,char * argv[]);

// static function declare and definition
void
usage()
{
    printf("Usage:tcpcli <IPAddress>.\n");
}

void
print_error(const char * error_str)
{
    printf("%s and error code = %d.\n",error_str,errno);
}

// main function
int
main(int argc,char * argv[])
{
    connectToServer(argc,argv);
    return EXIT_SUCCESS;
}

// feature function definition

int 
connectToServer(int argc,char * argv[])
{
    if(2!=argc)
    {
        usage();
        return EXIT_FAILURE;
    }
    int sockfd = -1;
    SAI servAddr;

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        print_error("create socket fd failed");
        return EXIT_FAILURE;
    }
    bzero(&servAddr,sizeof(SAI));

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET,argv[1],&servAddr.sin_addr);

    if(connect(sockfd,(SA*)&servAddr,sizeof(SAI)) < 0)
    {
        // printf("create socket fd failed and error code = %d\n,",errno);
        print_error("connect server failed");
        return EXIT_FAILURE;
    }
    // change input from data
    FILE * fptrMakefile = fopen("Makefile","r");
    if(NULL == fptrMakefile)
    {
        str_cli(stdin,sockfd);
    }
    str_cli(fptrMakefile,sockfd);
    close(sockfd);
    return EXIT_SUCCESS;
}

void
str_cli(FILE * fp,int sockfd)
{
    char sendline[BUFFER_SIZE], recvline[BUFFER_SIZE];
    bzero(sendline,BUFFER_SIZE);
    bzero(recvline,BUFFER_SIZE);

    while(fgets(sendline,BUFFER_SIZE,fp)!=NULL)
    {
        write(sockfd,sendline,strlen(sendline));
        if(read(sockfd,recvline,BUFFER_SIZE) == 0)
        {
            print_error("str_cli:server terminated prematurely");
            return;
        }
        // print to stdout FILE 
        fputs(recvline,stdout);
        bzero(recvline,BUFFER_SIZE);
    }
}