

// linux
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>

// c std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <signal.h>

// macro
#define SERVER_PORT 8010
#define BUFFER_SZIE 1460

// typedef
typedef struct sockaddr     SA;
typedef struct sockaddr_in  SAI;

// static variable
static int count = 0;


// function declare
void udp_srv();

void dg_echo(int sockfd,SA * cliAddr,socklen_t len);

void dg_echo_v2(int sockfd,SA * cliAddr,socklen_t clilen);

void recvfrom_int(int signo);

// main function
int
main(int argc,char * argv[])
{

    udp_srv();
    return EXIT_SUCCESS;
}

void
udp_srv()
{
    int     sockfd = -1;
    SAI     servAddr,cliAddr;

    if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
    {
        printf("create sock fd failed and error code = %d.\n",errno);
        return;
    }
    bzero(&servAddr,sizeof(servAddr));
    bzero(&cliAddr,sizeof(cliAddr));

    servAddr.sin_family      = AF_INET;
    servAddr.sin_port        = htons(SERVER_PORT);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // inet_pton(AF_INET,"172.27.135.187",&servAddr.sin_addr);

    assert(bind(sockfd,(SA*)&servAddr,sizeof(SAI))==0);

    // dg_echo(sockfd,(SA*)&cliAddr,sizeof(SAI));
    dg_echo_v2(sockfd,(SA*)&cliAddr,sizeof(SAI));

    close(sockfd);
}
void
dg_echo(int sockfd,SA * cliAddr,socklen_t clilen)
{
    int         n;
    socklen_t   len;
    char        mesg[BUFFER_SZIE];
    for(; ;)
    {
        len = clilen;
        bzero(mesg,BUFFER_SZIE);
        printf("wait msg.....\n");
        n = recvfrom(sockfd,mesg,BUFFER_SZIE,0,cliAddr,&len);

        printf("recv line = %s.\n",mesg);
        sendto(sockfd,mesg,n,0,cliAddr,len);
    }
}
void
dg_echo_v2(int sockfd,SA * cliAddr,socklen_t clilen)
{
    socklen_t len;

    char mesg[BUFFER_SZIE];

    signal(SIGINT,recvfrom_int);

    for( ;; )
    {
        len = clilen;
        recvfrom(sockfd,mesg,BUFFER_SZIE,0,cliAddr,&len);
        count++;
    }
}
void
recvfrom_int(int signo)
{
    printf("\nreceived %d datagrams\n",count);
}

