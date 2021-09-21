
/**
 * @file main.cpp
 * @author huangj (1435054809@qq.com)
 * @brief 利用gethostbyname 和 gethostbyaddr 函数获取对应的主机名称和别名 以及 IP地址
 * @version 0.1your name
 * @date 2021-09-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// linux
#include <netdb.h>      // for hostent struct
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// c std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void gethostbyname_func();

void whichProtocol(int protocolType); 

void printAllaliases(char ** aliases);

void printAllAddress(char ** address);

void accordingByDns(const char * name);

void hostByAddr(in_addr * addr);

void getAllAddress(char ** address);

/**
 * @brief main function
 * 
 */

int main(int argc,char * argv[])
{

    gethostbyname_func();
	accordingByDns("github.global.ssl.fastly.net");
	accordingByDns("www.baidu.com");
    accordingByDns("github.com");
    return EXIT_SUCCESS;
}

/**
 * @brief 根据传入的主机名称 映射成 IPV4地址 系统调用函数为gethostbyname 
 * 
 */
void gethostbyname_func()
{
    struct hostent * sh = NULL;
    // 可以通过hostname获取主机名称
    sh = gethostbyname("iZbp12ibqc0f9rucd631pmZ");
    
    if(!sh)
    {
        printf("return struct hostent is NULL.\n");
        return;
    }
    // offical name
    printf("offical name : %s.\n",sh->h_name);
    whichProtocol(sh->h_addrtype);
    printAllaliases(sh->h_aliases);
    printAllAddress(sh->h_addr_list);
	getAllAddress(sh->h_addr_list);
    // protocol family
}

void whichProtocol(int protocolType)
{
    switch(protocolType)
    {
    case  AF_INET:
    {
        printf("protocol is AF_INET.\n");
        break;
    }   
    }
}
void printAllAddress(char ** address)
{
    // only for ipv4
    static char buffer[32];
    printf("--------------all address-------------\n");
    while((*address) != NULL)
    {
        inet_ntop(AF_INET,(*address),buffer,sizeof(buffer));
        printf("%s\n",buffer);
        address++;
    }
}


void getAllAddress(char ** address)
{
	
	while((*address)!=NULL)
	{
		hostByAddr((in_addr*)(*address));
		address++;	
	}
}

void printAllaliases(char ** aliases)
{
    printf("----------all aliases name-------------\n");
    while((*aliases) != NULL)
    {
        printf("%s.\n",(*aliases));
        aliases++;
    }
}

// 根据一个域名来获取IP地址
void accordingByDns(const char * name)
{
	struct hostent * sh = NULL;
	sh = gethostbyname(name);

	if(!sh)
	{	
		printf("result is empty.\n");
		return;
	}
	printf("offical name : %s.\n",sh->h_name);
	printAllaliases(sh->h_aliases);
	printAllAddress(sh->h_addr_list);

	getAllAddress(sh->h_addr_list);
}

/*
 *	调用gethostbyaddr函数 实现反向转换
 *
 */

void hostByAddr(in_addr * addr)
{
	// 这个addr的结构为in_addr结构
	struct hostent * sh = NULL;
	sh = gethostbyaddr((void *)addr,4,AF_INET);
	if(!sh)
	{
		printf("%s.\n",hstrerror(h_errno));
		return;
	}
	printf("offical name : %s.\n",sh->h_name);
	whichProtocol(sh->h_addrtype);
	printAllaliases(sh->h_aliases);
	printAllAddress(sh->h_addr_list);
}

