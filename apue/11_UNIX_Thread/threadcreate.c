
#include "apue.h" 
#include<pthread.h>

pthread_t ntid;
void printids(const char *s)
{
    pid_t       pid;
    pthread_t   tid;

    pid=getpid();
    tid=pthread_self();

    printf("%s pid is %lu tid is %luu (0x%1x)\n",s,(unsigned long)pid,(unsigned long)tid, (unsigned long)tid);
}
void * thr_fn(void *arg)
{
    printids("new thread ");
    return ((void *)0);
}
int main(void)
{
    int err ;
    err=pthread_create(&ntid,NULL,thr_fn,NULL);
    if(err!=0)
    {
        err_exit(err,"can't create thread \n");
    }
    printids("main thread:");
    sleep(4);
    exit(0);
}
