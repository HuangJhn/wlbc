
// linux
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

// c std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#define SERVER_PORT 8010
#define BUFFER_SIZE 1460
// typedef
typedef struct sockaddr     SA;
typedef struct sockaddr_in  SAI;

// function declare
void sctpstr_cli(FILE * fp,int sockfd,SA * serverAddress,socklen_t tolen);
void sctp_client(const char * ip);

// main function
int
main(int argc,char * argv[])
{
    if(2 != argc)
    {
        printf("Usage: %s <server address>\n",argv[0]);
        return EXIT_FAILURE;
    }
    sctp_client(argv[1]);
    return EXIT_SUCCESS;
}
void
sctp_client(const char * ip)
{
    int         sockfd = 0;

    sockfd = socket(AF_INET,SOCK_SEQPACKET,IPPROTO_SCTP);

    if (sockfd < 0)
    {
        return;
    }
    SAI         serverAddress;
    bzero(&serverAddress,sizeof(serverAddress));
    serverAddress.sin_family  =  AF_INET;
    serverAddress.sin_port    = htons(SERVER_PORT);
    inet_pton(AF_INET,ip,&serverAddress.sin_addr);

    // struct sctp_event_subscrible    events;
    struct sctp_event_subscribe     events;
    bzero(&events,sizeof(events));

    events.sctp_data_io_event = 1;
    setsockopt(sockfd,IPPROTO_SCTP,SCTP_EVENTS,&events,sizeof(events));

    sctpstr_cli(stdin,sockfd,(SA*)&serverAddress,sizeof(serverAddress));
}
void sctpstr_cli(FILE * fp,int sockfd,SA * serverAddress,socklen_t tolen)
{
    typedef struct sctp_sndrcvinfo SSSRI;
    SAI     peerAddress;
    SSSRI   sri;
    char       sendBuffer[BUFFER_SIZE], recvBuffer[BUFFER_SIZE];
    socklen_t  len;
    int out_sz,rd_sz;
    int msg_flags = 0;

    bzero(sendBuffer,sizeof(sendBuffer));
    bzero(recvBuffer,sizeof(recvBuffer));

    while(fgets(sendBuffer,BUFFER_SIZE,stdin) != NULL)
    {
        if(sendBuffer[0] != '[')
        {
            printf("Error, line must be of the from '[streamnum]text'\n");
            continue;
        }
        sri.sinfo_stream = atoi(&sendBuffer[1]);

        out_sz = strlen(sendBuffer);

        sctp_sendmsg(sockfd,
                     sendBuffer,
                     out_sz,
                     serverAddress,
                     tolen,
                     0,
                     0,
                     sri.sinfo_stream,
                     0,
                     0
                     );
        len = sizeof(peerAddress);
        // recv msg
        rd_sz = sctp_recvmsg(sockfd,
                             recvBuffer,
                             BUFFER_SIZE,
                             (SA*)&peerAddress,
                             &len,&sri,
                             &msg_flags);

        // 服务将sinfo_stream　进行加操作
        // sinfo_ssn 对应的是流序列号 即 这条流所积累的序号 从0开始往上叠加
        printf("From str : %d seq: %d (assoc:0x%x) : ",sri.sinfo_stream,sri.sinfo_ssn,(u_int)sri.sinfo_assoc_id);
        printf("%.*s",rd_sz,recvBuffer);
    }
}

// 模拟丢包率
// tc qdisc add dev lo root netem loss 1%   // 添加丢包率
// tc qdisc del dev lo root netem loss 30%  // 删除丢包率

