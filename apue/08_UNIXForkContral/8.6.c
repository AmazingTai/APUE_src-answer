#include "apue.h"

int
main(void)
{
    pid_t   pid;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid == 0)
        exit(0);

    sleep(4);
    system("ps ao pid,ppid,state,tty,command");
    exit (0);
}
