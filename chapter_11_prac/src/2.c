/**
 * @file 2.c
 * @author huangj (1435054809@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-21
 * 
 * 
 */

#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

void server(int flag);

int main(int argc,char * agrv[])
{
    server(argc);
    return EXIT_SUCCESS;
}
// tcp
void server(int flag)
{
    // bind * address
    struct sockaddr_in server;
    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port   = htons(8010);

    if(flag == 1)
    {
        server.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        inet_pton(AF_INET,"192.168.16.4",&server.sin_addr);
        // struct hostent * host_info = NULL;
        // char host_name[100];
        // bzero(host_name,100);
        // gethostname(host_name,100);

        // host_info = gethostbyname(host_name);
        // if(!host_info)
        // {
        //     printf("gethostbyname function failed\n");
        //     return;
        // }
        // struct in_addr * tmp = *host_info->h_addr_list;
        // server.sin_addr = *tmp;
    }

    // sock_dgram
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd < 0)
    {
        return;
    }
    int on = 1;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    assert(bind(sockfd,(struct sockaddr*)&server,sizeof(server)) == 0);

    struct sockaddr_in client_address;
    socklen_t len;
    char buffer[1024];
    bzero(buffer,1024);
    bzero(&client_address,sizeof(client_address));

    len = sizeof(client_address);

    recvfrom(sockfd,buffer,1024,0,(struct sockaddr*)&client_address,&len);
    time_t tm = time(NULL);
    (void)tm;

}

