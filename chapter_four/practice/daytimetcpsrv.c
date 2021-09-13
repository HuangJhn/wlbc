
#include<sys/socket.h>
#include<sys/time.h>
#include<arpa/inet.h>

#include<unistd.h>
#include<errno.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<time.h>

#define MAXLINE 1024
#define BACKLOG 5

int time_service(int argc,char * argv[]);

int
main(int argc,char * argv[])
{
    if(time_service(argc,argv) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
int 
time_service(int argc,char * argv[])
{
    int     listenfd,connfd;
    struct sockaddr_in  servaddr;
    char    buffer[MAXLINE];

    time_t ticks;

    if((listenfd = socket(AF_INET,SOCK_STREAM,0)) <= 0)
    {
        // error no.
        printf("create socket fd failed error code = %d.\n",errno);
        return EXIT_FAILURE;
    }

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    // servaddr.sin_port = htons(13);
    servaddr.sin_port = htons(9999);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // assert(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) >= 0);

    listen(listenfd,BACKLOG);

    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(struct sockaddr_in);

    getsockname(listenfd,(struct sockaddr * )&cliaddr,&len);
            char ipBuffer[16];
        inet_ntop(AF_INET,&cliaddr.sin_addr,ipBuffer,16);

    printf("connection from %s, port = %d.\n",ipBuffer,ntohs(cliaddr.sin_port));

    for(;;)
    {

        bzero(buffer,sizeof(buffer));
        connfd = accept(listenfd,(struct sockaddr*)&cliaddr,&len);
        ticks = time(NULL);

        //写入26个字符(\r\n占用两个字符)
        snprintf(buffer,sizeof(buffer),"%.24s\r\n",ctime(&ticks));
        // write(connfd,buffer,strlen(buffer));

        // include '\0'
        for(size_t index = 0;index <= strlen(buffer);index++)
        {   
            write(connfd,&buffer[index],1);
        }

        inet_ntop(AF_INET,&cliaddr.sin_addr,ipBuffer,16);
        printf("connection from %s, port = %d.\n",ipBuffer,ntohs(cliaddr.sin_port));
        //close socket fd
        close(connfd);
    }
    close(listenfd);
    return EXIT_SUCCESS;
}

