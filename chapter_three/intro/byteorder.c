
#include<sys/socket.h>
#include<unistd.h>
#include<sys/time.h>
#include<stdio.h>
#include<stdlib.h>

//判断当前机器的的字节序:大端字节序和小端字节序

int
main(int argc,char * argv[])
{
    union
    {
        short s;
        char  c[sizeof(short)];
    }un;

    un.s = 0x0102;
    // printf("%s: ",CPU_VENDOR_OS);
    if(sizeof(short) == 2)
    {
        if(un.c[0] == 0x01 && un.c[1] == 0x02)
        {
            printf("big endian.\n");
        }
        else if(un.c[0] == 0x02 && un.c[1] == 0x01)
        {
            printf("little endian.\n");
        }
        else 
        {
            printf("unknow.\n");
        }
    }
    else
    {
        printf("sizeof(short) == %lu.\n",sizeof(short));
    }
    return EXIT_SUCCESS;
}