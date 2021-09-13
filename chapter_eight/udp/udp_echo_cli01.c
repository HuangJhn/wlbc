

// linux
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

// c std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// macro
#define SERVER_PORT 8010
#define BUFFER_SIZE 1460

// typedef 
typedef struct sockaddr     SA;
typedef struct sockaddr_in  SAI;

// function declare
void udp_cli(char * ip);

void dg_cli(FILE * fp,int sockfd,SA * srvAddr,socklen_t srvlen);
void dg_cli_v2(FILE * fp,int sockfd,const SA * pservaddr,socklen_t servlen);

// main function
int
main(int argc,char * argv[])
{
    if(2 != argc)
    {
        printf("Usage: %s <IPaddress>.\n",(argv[0]));
        return EXIT_FAILURE;
    }
    udp_cli(argv[1]);
    return EXIT_SUCCESS;
}
// 此函数是标准输入 根据输入的内容 使用udp协议发送 到对应的udp服务器 ip地址需要使用命令参数输入
// 端口为宏SERVER_PORT
void
udp_cli(char * ip)
{
    int     sockfd;
    if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
    {
        printf("create sock fd failed and error code = %d.\n",errno);
        return;
    }
    SAI     srvAddr;
    socklen_t srvlen = sizeof(SAI);
    bzero(&srvAddr,sizeof(SAI));

    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port   = htons(SERVER_PORT);

    inet_pton(AF_INET,ip,&srvAddr.sin_addr);

    // bind self sockfd
    // SAI     cliAddr;
    // bzero(&cliAddr,sizeof(cliAddr));
    // cliAddr.sin_family = AF_INET;
    // cliAddr.sin_port   = htons(56610);
    // inet_pton(AF_INET,"127.0.0.1",&cliAddr.sin_addr);
    // assert(    bind(sockfd,(SA*)&cliAddr,sizeof(cliAddr)) == 0);

    // dg_cli(stdin,sockfd,(SA*)&srvAddr,srvlen);
    dg_cli_v2(stdin,sockfd,(SA*)&srvAddr,srvlen);

    close(sockfd);
}
void
dg_cli(FILE * fp,int sockfd,SA * srvAddr,socklen_t srvlen)
{
    int     n;
    char    sendline[BUFFER_SIZE],recvline[BUFFER_SIZE];

    bzero(sendline,BUFFER_SIZE);
    bzero(recvline,BUFFER_SIZE);
    // while(("%s",sendline)!=0)
    fgets(sendline,BUFFER_SIZE,fp);
    while(fgets(sendline,BUFFER_SIZE,fp)!=NULL)
    {
        n = sendto(sockfd,sendline,strlen(sendline),0,srvAddr,srvlen);
        
        printf("send size = %d.\n",n);

        n = recvfrom(sockfd,recvline,BUFFER_SIZE,0,NULL,NULL);

        printf("recv line = %s.\n",recvline);

        bzero(sendline,BUFFER_SIZE);
        bzero(recvline,BUFFER_SIZE);
    }
}
void
dg_cli_v2(FILE * fp,int sockfd,const SA * pservaddr,socklen_t servlen)
{
    int i = 0;
    char buffer[BUFFER_SIZE + 200];

    int size = BUFFER_SIZE;

    for(i = 0; i < size; ++i)
    {
        ssize_t size = sendto(sockfd,buffer,BUFFER_SIZE + 200,0,pservaddr,servlen);
        printf("send mesage %ld.\n",size);
    }
}