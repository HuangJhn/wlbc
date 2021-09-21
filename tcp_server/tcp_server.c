

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>

// c std
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define BACKLOG 10

int tcp_server(const char * host_name,const char * server_name);

// test function
/**
 * @brief 测试tcp_server函数
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc,char * argv[])
{
    char buffer[32];
    bzero(buffer,32);
    gethostname(buffer,32);
    int sockfd = tcp_server(buffer,"chargen");
    if(sockfd < 0)
    {
        printf("failed.\n");
        return EXIT_FAILURE;
    }
    // accept
    int clientfd = accept(sockfd,NULL,NULL);
    srand(time(NULL));
    for(;;)
    {
        char ch = rand()%10 + 48;
        write(clientfd,&ch,1);
    }
    close(clientfd);
    close(sockfd);
    return EXIT_SUCCESS;
}
/**
 * @brief 监听对应的服务
 * 
 * @param host_name 
 * @param server_name 
 * @return int 
 */
int tcp_server(const char * host_name,const char * server_name)
{
    struct addrinfo * result;
    struct addrinfo   hints;
    
    // hints
    bzero(&hints,sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family   = AF_UNSPEC;

    if(getaddrinfo(host_name,server_name,&hints,&result)!=0)
    {
        // failed
        return -1;
    }
    int sockfd = -1;
    struct addrinfo * tmp = result;
    while(tmp!=NULL)
    {
        if((sockfd = socket(tmp->ai_family,tmp->ai_socktype,tmp->ai_protocol)) >= 0)
        {
            int on = 1;
            // not use 127.0.0.1 ip connect the server
            assert(bind(sockfd,tmp->ai_addr,tmp->ai_addrlen) == 0);
            setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
            listen(sockfd,BACKLOG);
            // create success
            printf("listening\n");
            break;
        }
        tmp = tmp->ai_next;
    }
    if(tmp == NULL)
    {
        // 创建失败
        sockfd = -1;
    }
    freeaddrinfo(result);
    return sockfd;
}
