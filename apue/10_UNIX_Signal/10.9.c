#include "apue.h"

#include <errno.h>

int all_signo[] = {1, 2, 3, 4, 5, 6, 7, 8, 
9, 10, 11, 12 , 13, 14, 15, 17, 
18, 19, 20, 21, 22, 23, 24, 25, 
26, 27, 28, 29, 30, 31, 34, 35, 
36, 37, 38, 39, 40, 41, 42, 43, 
44, 45, 46, 47, 48, 49, 50, 51, 
52, 53, 54, 55, 56, 57, 58, 59, 
60, 61, 62, 63, 64};

char all_sigstr[61][20] = {"SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT", "SIGBUS", "SIGFPE",
"SIGKILL", "SIGUSR1", "SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM", "SIGCHLD",
"SIGCONT", "SIGSTOP", "SIGTSTP", "SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU", "SIGXFSZ",
"SIGVTALRM", "SIGPROF", "SIGWINCH", "SIGIO", "SIGPWR", "SIGSYS", "SIGRTMIN", "SIGRTMIN+1",
"SIGRTMIN+2", "SIGRTMIN+3", "SIGRTMIN+4", "SIGRTMIN+5", "SIGRTMIN+6", "SIGRTMIN+7", "SIGRTMIN+8", "SIGRTMIN+9",
"SIGRTMIN+10", "SIGRTMIN+11", "SIGRTMIN+12", "SIGRTMIN+13", "SIGRTMIN+14", "SIGRTMIN+15", "SIGRTMAX-14", "SIGRTMAX-13",
"SIGRTMAX-12", "SIGRTMAX-11", "SIGRTMAX-10", "SIGRTMAX-9", "SIGRTMAX-8", "SIGRTMAX-7", "SIGRTMAX-6", "SIGRTMAX-5",
"SIGRTMAX-4", "SIGRTMAX-3", "SIGRTMAX-2", "SIGRTMAX-1", "SIGRTMAX"};

typedef struct sigstr{
    int signo;
    char *str;
    struct sigstr *next;
}SIGSTR;

void get_sig_str(SIGSTR *p_st){

    int i, j;
    for ( i = 0; i < 61; i++){
        insert(p_st, all_signo[i], all_sigstr[i], i);
    }
}

void pr_mask(const char *str)
{
    sigset_t sigset;
    int errno_save;
    errno_save=errno;
    int i=0;
    if(sigprocmask(0,NULL,&sigset))
    {
        err_ret("sigprocmask error");
    }
    else
    {
        printf("%s",str);
        for(i = 0 ;i<61;i++){
         if(sigismember(&sigset,all_sigstr[i]))
            printf("all_sigstr[%d] : %s",i,all_sigstr[i]);
        }
        printf("\n");
    }
    errno =errno_save;
}