

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void get_addr_info_test(const char * host_name,const char * service_name);

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc,char * argv[])
{

    // test case 1 that the host_name is NULL and service name is daytime
    printf("test case 1 that the host_name is NULL and service name is daytime.\n");
    get_addr_info_test(NULL,"daytime");

    // test case 2 that the host_name is NULL and service name is https
    printf("test case 2 that the host_name is NULL and service name is https.\n");
    get_addr_info_test(NULL,"https");

    // test case 3 that the host_name is local host name and service name is http
    printf("test case 3 that the host_name is local host name and service name is http.\n");
    get_addr_info_test("iZbp12ibqc0f9rucd631pmZ","http");
    // get_addr_info_test("iZbp12ibqc0f9rucd631pmZ","daytime");

    // test case 4 that host_name is a IPV4 and service name is daytime
    printf("test case 4 that host_name is a IPV4 and service name is daytime.\n");
    get_addr_info_test("0.0.0.0","daytime");

    // test case 5 that host_name is a IPV6 and service name is daytime
    printf("test case 5 that host_name is a IPV6 and service name is daytime.\n");
    get_addr_info_test("0::0","daytime");

    // test case 6 that use www.baidu.com as host_name and https as service name
    printf("test case 6 that use www.baidu.com as host_name and https as service name.\n");
    get_addr_info_test("www.baidu.com","https");

    // test case 7 that use www.baidu.com as host_name and https as service name
    printf("test case 7 that use www.baidu.com as host_name and daytime as service name.\n");
    get_addr_info_test("www.baidu.com","daytime");

    // test case 8 that in /etc/service add myself service name and port protocol
    // 如果在/etc/service中添加了对应的服务那么就会成功，如果没有就会失败
    printf("test case 8 that in /etc/service add myself service name and port protocol.\n");
    get_addr_info_test("iZbp12ibqc0f9rucd631pmZ","huangj");
    return EXIT_SUCCESS;
}
/**
 * @brief Get the addr info test object
 * 
 * @param host_name 
 * @param service_name 
 */
void get_addr_info_test(const char * host_name,const char * service_name)
{
    struct addrinfo hints;
    struct addrinfo *result;
    bzero(&hints,sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if(host_name != NULL)
    {
        hints.ai_flags    = AI_CANONNAME;   // is host_name is null and getaddrinfo will be failed
    }

    if(getaddrinfo(host_name,service_name,&hints,&result) != 0)
    {
        // get address info failed
        printf("get address info failed and error_code = %d.\n\n",h_errno);
        return;
    }
    printf("%s - success.\n\n",result->ai_canonname);
}