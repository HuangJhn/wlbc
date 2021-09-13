
// linux
#include<unistd.h>  // for fork function
// c std
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

void fork_func()
{
    //getppid return int type
    printf("simple print a line and print parent pid = %d.\n",getppid());
}

int
main(int argc,char * argv[])
{
    printf("parent self pid = %d.\n",getpid());
    pid_t childPid = fork();
    {
        printf("child print child pid = %d.\n",getpid());
        fork_func();
        // return EXIT_SUCCESS;
    }
    printf("parent print child pit = %d.\n",childPid);
    //休眠可以观察父进程还没有进程的情况下，子进程的执行情况。
    sleep(10);
    return EXIT_SUCCESS;
}

//TOOD:分析输出
/*
line 1 : parent self pid = 4067.
line 2 : child print child pid = 4067.
line 3 : simple print a line and print parent pid = 1222.
line 4 : parent print child pit = 4068.
line 5 : root@iZbp12ibqc0f9rucd631pmZ:~/unixwlbc/chapter_four/fork_test/build# child print child pid = 4068.
line 6 : simple print a line and print parent pid = 1.
line 7 : parent print child pid = 0.
*/
/*
    第一行是在fork之前输出父进程的pid = 4067。
    第二行对应的main函数的第21行，这个是父进程调用的，所以输出的还是 4067。
    第三行是父进程调用getppid函数，获取的到一个数字1222 代表的是/bin/bash进程。
    第四行是父进程根据fork函数返回的子进程pid输出，仅在父进程的pid上加1。
    第五行是开始子进程的执行，然后输出子进程的pid 与 返回父进程的一致。
    第六行是子进程调用函数fork_func的执行，调用getpid输出1表示的是父进程已经结束。
    第七行是输出子进程返回的0，而非对父进程返回子进程的pid
*/