/**
 * @file daemon_init.c
 * @author huangj (1435054809@qq.com)
 * @brief 创建守护进程
 * @version 0.1
 * @date 2021-09-25
 * 
 * 
 */
#include <unistd.h>
#include <errno.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/file.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXFD 64

int daemon_init(const char * pname,int facility)
{
    int     i = 0;
    pid_t   pid = 0;

    // first fork 
    if((pid = fork()) < 0)
    {
        // create child process failed
        return -1;
    }
    else if( pid > 0)
    {
        // exit parent process
        exit(0);
    }
    // child 1 continuing
    // 设置当前进程为leader
    if(setsid() < 0)
    {
        return -1;
    }
    // 子进程fork一个子进程会触发SIGHUB信号
    signal(SIGHUP,SIG_IGN);
    if((pid = fork()) < 0)
    {
        printf("init.\n");
        return -1;
    }
    else if(pid > 0)
    {
        // exit child process
        exit(0);
    }
    // child 2 continuing
    // chdir("/");

    // close off file descriptions
    for(i = 0;i < MAXFD; i++)
    {
        close(i);
    }
    // open stdin\stdout\stderr  and redirect to /dev/null
    open("./1.txt",O_RDONLY);
    open("./1.txt",O_RDWR);
    open("./1.txt",O_RDWR);

    openlog(pname,LOG_PID,facility);

    // success
    return 0;
}