#include "apue.h"

#define     SIZE 15
static void f1(void);
static void f2();

static void f1(void)
{
    if (vfork() < 0)
        err_sys("vfork error");
}

static void f2()
{
    char    buf[1000];
    int     i;
    for (i =0; i < 1000; i++)
        buf[i] = 0;
}


int main(void)
{
    f1();
    f2();
}

/*

函数f1调用vfork时，父进程的栈指针指向f1的函数的栈帧，
vfork使得子进程先执行然后从f1返回，接着子进程调用f2，
并且f2的栈帧覆盖了f1的栈帧
从f2返回后子进程调用_exit，这时栈中main栈帧一下的内容已经被f2修改了。
然后，父进程从vfork调用后回复继续，并从f1返回。
*/