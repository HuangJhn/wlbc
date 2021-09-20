/*
 *  @author : HuangJ
 * 
 *  @mail   : 1435054809@qq.com
 * 
 *  @msg : 利用sctp协议 实现一个标准输入的客户端 发送给对应的sctp回射服务器
 * 
 *  @time : Wed Sep 15 21:35:17 CST 2021
 * 
 */

// linux
#include <sys/socket.h>
#include <netinet/in.h> // must include in #include <netinet/sctp.h> before
#include <netinet/sctp.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>

// c std
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define SERVER_PORT 8010
#define BUFFER_SIZE 1460
#define SCTP_MAX_STREAM 9       // 按照目前来看流数量最大为9 还不到10

typedef struct sockaddr SA;
typedef struct sockaddr_in SAI;

void client(const char *address);
void sctpstr_cli(FILE *in, int sockfd, SA *server_address, socklen_t server_len);
void abortClose(int sockfd,SA * server_addr,socklen_t len);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Uage: %s <IPaddress>.\n", argv[0]);
        return EXIT_FAILURE;
    }
    client(argv[1]);
    return EXIT_SUCCESS;
}
/**
 * @brief 利用sctp协议连接服务器
 * 
 * @param  服务器ip地址
 */

void client(const char *address)
{
    int sockfd;
    SAI server_address;

    sockfd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
    if (sockfd < 0)
    {
        printf("create sockfd failed.\n");
        return;
    }
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, address, &server_address.sin_addr);

    struct sctp_event_subscribe events;
    bzero(&events, sizeof(events));

    events.sctp_data_io_event = 1;
    setsockopt(sockfd, IPPROTO_SCTP, SCTP_EVENTS, &events, sizeof(events));

    sctpstr_cli(stdin, sockfd, (SA *)&server_address, sizeof(server_address));
}
void sctpstr_cli(FILE *in, int sockfd, SA *server_address, socklen_t server_len)
{
    typedef struct sctp_sndrcvinfo SSSRI;
    struct sctp_sndrcvinfo sri;

    SAI address;
    socklen_t alen;

    char input_buffer[BUFFER_SIZE], recv_buffer[BUFFER_SIZE];

    bzero(input_buffer, BUFFER_SIZE);
    bzero(recv_buffer, BUFFER_SIZE);

    bzero(&sri, sizeof(sri));

    while (fgets(input_buffer, BUFFER_SIZE, in) != NULL)
    {
        size_t len = strlen(input_buffer);
        // 添加流
        for (int index = 0; index < SCTP_MAX_STREAM; index++)
        {
            sri.sinfo_stream = index + 1;
            printf("stream no = %d.\n",sri.sinfo_stream);
            snprintf(input_buffer + len -1, BUFFER_SIZE - len, ".%d.msg 1", index + 1);

            sctp_sendmsg(sockfd, input_buffer, strlen(input_buffer), server_address, server_len, 0, 0, sri.sinfo_stream, 0, 0);
        }
        for (int index = 0; index < SCTP_MAX_STREAM; index++)
        {
            alen = sizeof(address);
            sctp_recvmsg(sockfd, recv_buffer, BUFFER_SIZE, (SA *)&address, &alen, &sri, 0);
            printf("recv msg = %s and stream no %d.\n", recv_buffer,sri.sinfo_stream);
        }
        printf("clear last content.\n");
        bzero(input_buffer,BUFFER_SIZE);
        bzero(recv_buffer,BUFFER_SIZE);
    }
}

/**
 * @brief 粗暴关闭关联
 * 
 */
void abortClose(int sockfd,SA * server_addr,socklen_t len)
{
    char buffer[100];
    bzero(buffer,sizeof(buffer));
    strncpy(buffer,"goodbay",8);

    sctp_sendmsg(sockfd,buffer,8,server_addr,len,0,SCTP_ABORT,0,0,0);
}