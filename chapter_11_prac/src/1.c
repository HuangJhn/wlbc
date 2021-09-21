/**
 * @file 1.c
 * @author huangj (1435054809@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-21
 * 
 * 
 */

#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


void hostbyname(const char * host_name);

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc,char * argv[])
{
    // get local host name
    char buffer[32];
    bzero(buffer,32);
    gethostname(buffer,32);
    // test case 1 that use local host name 
    printf("test case 1 that use local host name \n");
    hostbyname(buffer);

    // test case 2 that use www.baidu.com as parameter
    printf("test case 2 that use www.baidu.com as parameter \n");
    hostbyname("www.baidu.com");    // if bind hosts with the www.baidu.com the  gethostbyaddr will success

    // test case 3 that use public ip 
    printf("test case 3 that use public ip \n");
    hostbyname("180.76.114.47");

    // test case 3 that bind host 
    printf("with github.com \n");
    hostbyname("github.com");
    return EXIT_SUCCESS;
}
/**
 * @brief 
 * 
 * @param host_name 
 */
void hostbyname(const char * host_name)
{
    struct hostent * host_info;

    if((host_info = gethostbyname(host_name)) == NULL)
    {
        printf("call gethostbyname failed and host name is %s.\n",host_name);
        return;
    }
    // check address info and call gethostbyaddr
    // create sockaddr struct variable
    struct sockaddr_in address;
    struct hostent * result;
    char buffer[32];
    char ** pptr = host_info->h_addr_list;
    while(*pptr!=NULL)
    {
        bzero(buffer,32);
        inet_ntop(host_info->h_addrtype,*pptr,buffer,32);
        // bzero(&address,sizeof(address));
        // address.sin_family = host_info->h_addrtype;
        // address.sin_port   = htons(80);     // use http protocol port
        // address.sin_addr.s_addr   = (*pptr);
        printf("hex ip address : %s .\n",buffer);
        if((result = gethostbyaddr(*pptr,host_info->h_length,host_info->h_addrtype)) != NULL)
        {
            printf("offical name : %s.\n\n",result->h_name);
        }
        else
        {
            printf("call gethostbyaddr failed.\n\n");
        }
        pptr++;      
    }
}
