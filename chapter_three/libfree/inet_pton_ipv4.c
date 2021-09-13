

#include<sys/socket.h>
#include<arpa/inet.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const char * 
inet_ntop(int family,const void * addrptr,char * strptr,size_t len)
{
    const u_char *p = (const u_char*)addrptr;
    if(AF_INET == family || PF_INET == family)
    {
        char temp[INET_ADDRSTRLEN]; // INET_ADDRSTRLEN = 16
        snprintf(temp,sizeof(temp),"%d.%d.%d.%d",p[0],p[1],[2],p[3]);   // 网络字节序号
        if(sizeof(temp) > len)
        {
            errno = ENOSPC;
            return (NULL);
        }
        strcpy(strptr,temp);

        return (strptr);
    }
    errno = EAFNOSUPPORT;
    return NULL;
}



