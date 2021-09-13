
// linux
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

// c std
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

// macro
#define SERVER_PORT     8010
#define BUFFER_SIZE     1460
#define BACKLOG         10

// typedef
typedef struct sockaddr     SA;
typedef struct sockaddr_in  SAI;

// function 
void sctp_server(const int max_stream_no);

// static function declare

int
main(int argc,char * argv[])
{
    int max_stream_no = 10;
    if (argc == 2)
    {
        max_stream_no = atoi(argv[1]);
    }
    sctp_server(max_stream_no);
    return EXIT_SUCCESS;
}

void
sctp_server(const int max_stream_no)
{
    int     listenfd = 0;
    int     error_code = 0;
    listenfd = socket(AF_INET,SOCK_SEQPACKET,IPPROTO_SCTP); // one for mutl
    if(listenfd < 0)
    {

        return;
    }
    SAI     serverAddress;
    bzero(&serverAddress,sizeof(serverAddress));
    // protocol ip and port
    serverAddress.sin_family      = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);   // INADDR_ANY
    serverAddress.sin_port        = htons(SERVER_PORT);

    assert(bind(listenfd,(SA*)&serverAddress,sizeof(serverAddress)) == 0); 

    // declare sctp_sndrcvinfo var
    struct sctp_sndrcvinfo  sri;
    struct sctp_event_subscribe evnts;

    bzero(&evnts,sizeof(evnts));
    evnts.sctp_data_io_event = 1;
    setsockopt(listenfd,IPPROTO_SCTP,SCTP_EVENTS,&evnts,sizeof(evnts));

    // forward to listen fd
    listen(listenfd,BACKLOG);

    char buffer[BUFFER_SIZE];
    SAI  clientAddress;
    socklen_t      len;
    int            rd_sz = 0;
    int            msg_flag = 0;
    int            stream_increment = 1; 
    for(;;)
    {
        bzero(buffer,BUFFER_SIZE);
        bzero(&clientAddress,sizeof(clientAddress));
        len = sizeof(clientAddress);
        
        rd_sz = sctp_recvmsg(listenfd,
                             buffer,
                             BUFFER_SIZE,
                             (SA*)&clientAddress,
                             &len,&sri,&msg_flag);
        if(stream_increment)
        {
            sri.sinfo_stream++;
            if(sri.sinfo_stream >= max_stream_no)
            {
                sri.sinfo_stream = 0;
            }
        }
        sctp_sendmsg(listenfd,
                     buffer,
                     rd_sz,
                     (SA*)&clientAddress,
                     len,
                     sri.sinfo_ppid,
                     sri.sinfo_flags,
                     sri.sinfo_stream,
                     0,
                     0);
    }

}
