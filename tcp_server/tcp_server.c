

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

#define BACKLOG 10

// test function
int main(int argc,char * argv[])
{

    return EXIT_SUCCESS;
}

int tcp_server(const char * host_name,const char * server_name)
{
    struct addrinfo * result;
    struct addrinfo * hints;
    
    // hints
    bzero(&hints,sizeof(hints));
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_family   = AF_UNSPEC;

    if(getaddrinfo(host_name,server_name,&hints,&result)!=0)
    {
        // failed
        return -1;
    }
    int sockfd = -1;
    struct addrinfo * tmp = result;
    while(tmp!=NULL)
    {
        if((sockfd = socket(tmp->ai_family,tmp->ai_addr,tmp->ai_protocol)) >= 0)
        {
            int on = 1;
            setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
            listen(sockfd,BACKLOG);
            // create success
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
