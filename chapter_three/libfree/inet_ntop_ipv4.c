

#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>
#include<unistd.h>

#include<stdio.h>
#include<stdlib.h>

// 1 if process the success,otherwise return the 0 to stand for failed
// ipv4
int
inet_pton(int family,const char * strptr,void * addrptr)
{
    if(AF_INET == family || PF_INET == family)
    {
        struct in_addr in_val;
        if(inet_aton(strptr,&in_val))
        {
            memcpy(addrptr,&in_val,sizeof(struct in_addr));
            return 1;
        }
        return 0;
    }
    errno = EAFNOSUPPORT;   // family protocol no support
    return -1;
}
