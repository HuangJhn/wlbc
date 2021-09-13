

#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>  // for NULL

int inet_pton_loose_helper()
{
    
}

int
inet_pton_loose(int family,const char * ip)
{
    if(NULL == ip)
    {   
        return -1;
    }
    switch(family)
    {
        case AF_INET:
        {
            struct sockaddr_in addr;
            bzero(&addr,sizeof(addr));

            int res = inet_pton(family,ip,&addr.sin_addr);
            if(0 == res)
            {
                printf("af_inet call inet_pton failed.\n");
                bzero(&addr,sizeof(addr));
                res = inet_aton(ip,&addr.sin_addr);
                if(0 == res)
                {
                    printf("af_inet call inet_aton failed addr = %d.\n",addr.sin_addr.s_addr);
                    return 0;
                }
                else
                {
                    printf("af_inet success addr = %d.\n",addr.sin_addr);
                }
            }
            else
            {
                printf("af_inet inet_pton success addr = %d.\n",addr.sin_addr);
            }
            break;
        }
        case AF_INET6:
        {
            // printf("AF_INET6.\n");
            struct sockaddr_in6 addr6;
            bzero(&addr6,sizeof(struct sockaddr_in6));

            int res = inet_pton(family,ip,&addr6.sin6_addr);
            // printf("%d.\n",res);
            if(0 == res)
            {
                printf("af_inet6 call inet_pton failed.\n");
                bzero(&addr6,sizeof(struct sockaddr_in6));

                res = inet_aton(ip,&addr6.sin6_addr);
                if(0 == res)
                {
                    printf("af_inet6 call inet_aton failed.\n");
                    return 0;
                }
                else
                {
                    printf("af_inet6 success addr = %d.\n",addr6.sin6_addr);
                }
            }
            else
            {
                printf("af_inet6 inet_pton success addr = %d.\n",addr6.sin6_addr);
            }
            break;
        }
    }
    return -1;
}
// ipv6:fe80::216:3eff:fe0d:4706
// ipv4:172.27.135.187
int
main(int argc,char * argv[])
{

    if(argc!=2)
    {
        printf("need ipv4 or ipv6 address");
        return EXIT_FAILURE;
    }
    // if(sizeof(argv[1]) > INET_ADDRSTRLEN)
    {
        // 输入一个ipv4的地址
        inet_pton_loose(AF_INET6,argv[1]);
        inet_pton_loose(AF_INET,argv[1]);   // 对照组
    }
    // else
    // {
    //     inet_pton_loose(AF_INET,argv[1]);
    // }
    return EXIT_SUCCESS;
}