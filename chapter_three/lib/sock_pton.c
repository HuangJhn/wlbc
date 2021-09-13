
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

char * 
sock_ntop(const struct sockaddr * sa,socklen_t salen)
{
    char    portstr[8]; // 端口的范围1-65535
    static  char str[128];

    switch(sa->sa_family)
    {
        case AF_INET:
        {
            struct sockaddr_in * sin = (struct sockaddr_in*)sa;

            if(inet_ntop(AF_INET,&sin->sin_addr,str,sizeof(str)))
            {
                return NULL;
            }
            if(ntohs(sin->sin_port)!=0)
            {
                snprintf(portstr,sizeof(portstr),":%d",ntohs(sin->sin_port));

                strcat(str,portstr);
            }
            return (str);
        }
    }
}

