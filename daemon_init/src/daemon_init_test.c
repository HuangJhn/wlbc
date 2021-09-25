/**
 * @file daemon_init_test.c
 * @author huangj (1435054809@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-25
 * 
 * 
 */

#include <unistd.h>
#include <syslog.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

void SIGTERM_proc(int sigNo)
{
    syslog(LOG_WARNING,"the process killed");
}

const char * sock_ntop(struct sockaddr * sa,socklen_t len)
{

    switch(len)
    {
    case sizeof(struct sockaddr_in):
    {
        struct sockaddr_in * sai = (struct sockaddr_in*)sa;
        static char buffer[40];
        bzero(buffer,40);
        inet_ntop(sai->sin_family,&sai->sin_addr,buffer,32);
        uint16_t port = ntohs(sai->sin_port);
        snprintf(buffer+strlen(buffer),6,":%d",port);
        return buffer;
    }
    case sizeof(struct sockaddr_in6):
    {

    }
    }
}

void daemon_init_test(int argc,char * argv[])
{
    // 第一步就是检查命令参数
    // 第二步就是创建一个守护进程 即 调用daemon_init函数
    // 第三步就是创建套接字并监听
    // 第四步就是等待客户的连接
    printf("init.\n");
    if (argc != 3)
    {
        
        return;
    }
    if(daemon_init(argv[0],0) < 0)
    {   
        // 当返回-1 表示创建守护进程失败了
        printf("create daemon failed.\n");
        return;
    }
    int sockfd = 0;
    socklen_t len = 0;
    sockfd = tcp_listen(argv[1],argv[2],&len);
    if(sockfd < 0)
    {
        syslog(LOG_WARNING,"监听套接字错误");
        return;
    }

    // add SIGTERM process function
    signal(SIGTERM,SIGTERM_proc);

    // printf("test stdin stdout stderr");
    char buffere[32];
    bzero(buffere,32);
    // no check the buffer length
    strcpy(buffere,"test stdin stdout stderr");
    write(fileno(stdout),buffere,strlen(buffere));

    socklen_t client_len = 0;
    struct sockaddr * client_addr = (struct sockaddr * )malloc(len);

    char buffer[100];
    for(;;)
    {
        client_len = len;
        int clientfd = accept(sockfd,client_addr,&client_len);

        syslog(LOG_INFO,"%s",sock_ntop(client_addr,len));

        bzero(buffer,100);
        time_t ticks = time(NULL);

        // /var/log/syslog
        snprintf(buffer,100,"%.24s\r\n",ctime(&ticks));

        write(clientfd,buffer,strlen(buffer));

        close(clientfd);
    }
    close(sockfd);
}

int main(int argc,char * argv[])
{
    daemon_init_test(argc,argv);
    return EXIT_SUCCESS;
}

