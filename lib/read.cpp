
#include "read.h"
#include "error.h"

static int error_code = 0;

size_t Read(int __fd,char * __buffer,size_t __len)
{
    // 传入的长度参数为空 直接返回0
    if (0 >= __len)
    {
        return 0;
    }
    bzero(__buffer,__len);

    size_t readLen = 0;
    readLen = read(__fd,__buffer,__len);

    if (readLen < 0)
    {
        // 对于非EINTR错误 需要打印出信息
        if (errno != EINTR)
        {
            error_code = errno;
            printfError(error_code,"read failed");
        }
        return -1;
    }
    return readLen;
}
