#include "apue.h"
#include <errno.h>

void pr_mask(const char *str)
{
    sigset_t sigset;
    int errno_save;
    errno_save=errno;
    if(sigprocmask(0,NULL,&sigset))
    {
        err_ret("sigprocmask error");
    }
    else
    {
        printf("%s",str);
        if(sigismember(&sigset,SIGINT))
            printf("SIGINT");
        if(sigismember(&sigset,SIGQUIT))
            printf("QUIT");
        if(sigismember(&sigset,SIGUSR1))
            printf("USR1");
        if(sigismember(&sigset,SIGUSR2))
            printf("USR2");
        printf("\n");
    }
    errno =errno_save;
}