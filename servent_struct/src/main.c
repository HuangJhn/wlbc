/**
 * @file main.cpp
 * @author huangj (1435054809@qq.com)
 * @brief 
 * @version 0.1your name
 * @date 2021-09-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
// linux
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>

// c std
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void getServerByServerName(const char * serverName,const char * protocolName);

void getServerByPortNumber(const int port,const char * protocolName);

void printServerName(const char * serverName);

void printServerAliases(char ** aliasesName);

void printServerPort(const int networkPort);

void printServerProtocolName(const char * protocolName);

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc,char * argv[])
{
    printf("%ld.\n",sizeof(struct sockaddr_in));
    // flow(argc,argv);
    // first test case 
    getServerByServerName("ftp","tcp");

    // second test case
    getServerByServerName("ftp",NULL);

    // three test case
    getServerByServerName("daytime",NULL);

    // fouth test case
    getServerByServerName("ssh",NULL);

    // five test case 
    getServerByServerName("ping","udp");

    getServerByServerName("chargen","tcp");


    printf("--------------------------------------");

    // for(int index = 0; index < 1000; index++)
    // {
    //     getServerByPortNumber(index,NULL);
    // }
    return EXIT_SUCCESS;
}
/**
 * @brief Get the Server By Server Name object
 * 
 * @param serverName 
 * @param protocolName 
 */
void getServerByServerName(const char * serverName,const char * protocolName)
{
    struct servent * ss = NULL;
    ss = getservbyname(serverName,protocolName);
    // check ss
    if(!ss)
    {
        printf("");
        return;
    }
    printServerName(ss->s_name);
    printServerAliases(ss->s_aliases);
    printServerPort(ss->s_port);
    printServerProtocolName(ss->s_proto);
}
/**
 * @brief Get the Server By Port Number object
 * 
 * @param port 
 * @param protocolName 
 */
void getServerByPortNumber(const int port,const char * protocolName)
{
    struct servent * ss;
    uint16_t netPort =  htons(port);
    ss = getservbyport(netPort,protocolName);
    // check ss
    if(!ss)
    {
        return;
    }
    printServerName(ss->s_name);
    printServerAliases(ss->s_aliases);
    printServerPort(ss->s_port);
    printServerProtocolName(ss->s_proto);
}
/**
 * @brief 输出服务名称
 * 
 * @param serverName 
 */
void printServerName(const char * serverName)
{
    printf("\nserver name : %s.\n",serverName);
}
/**
 * @brief 输出服务别名
 * 
 * @param aliasesName 
 */
void printServerAliases(char ** aliasesName)
{
    printf("server aliases name : ");
    while(*aliasesName!=NULL)
    {
        printf("%s\t",*aliasesName);
        aliasesName++;
    }
    printf("\n");
}
/**
 * @brief 输出端口
 * 
 * @param networkPort 网络字节序端口
 */
void printServerPort(const int networkPort)
{
    uint16_t port = ntohs(networkPort);
    printf("port : %d.\n",port);
}

/**
 * @brief 输入服务所用的协议
 * 
 * 
 * @param protocolName 协议名称
 * 
 */
void printServerProtocolName(const char * protocolName)
{
    printf("server protocol name : %s .\n",protocolName);
}