#ifndef _SIGNAL_H_
#define _SIGNAL_H_

// linux
#include <sys/signal.h>

// c std
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

// typedef
typedef void (*sigFunc)(int);

sigFunc signal(int signo,sigFunc func)
{
    struct sigaction act,oact;
    
    act.sa_handler = func;
    // 填充sa_mask
    sigisemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if(signo == SIGALRM)
    {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;   // SunOs 4.x
#endif
    }
    else
    {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;    // SVR4 4.4BSD
#endif
    }
    if(sigaction(signo,&act,&oact) < 0)
    {   
        // 设置信号处理函数失败
        return(SIG_ERR);
    }
    return (oact.sa_handler);
}



// int test();

// int 
// func()
// {

//     int (*fun)(void);
//     testFunc t = test;
// }
#endif //!_SIGNAL_H_