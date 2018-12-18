#include "apue.h" 
#include<pthread.h>


pthread_mutex_t lock1=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2=PTHREAD_MUTEX_INITIALIZER;


void prepare(void)
{
    int err;
    printf("preparing locks .. \n");
    if((err=pthread_mutex_lock(&lock1))!=0)
        err_cont(err,"can't lock lock1 in prepare handler\n");
    if((err=pthread_mutex_lock(&lock2))!=0)
        err_cont(err,"can't lock lock2 in prepare handler\n");
}
void parent(void)
{
    int err;
    printf("parent unlocking locks .. \n");
    if((err=pthread_mutex_unlock(&lock1))!=0)
        err_cont(err,"can't unlock lock1 in parent handler\n");
    if((err=pthread_mutex_unlock(&lock2))!=0)
        err_cont(err,"can't unlock lock2 in parent handler\n");
}
void child(void)
{
    int err;
    printf("child unlocking locks .. \n");
    if((err=pthread_mutex_unlock(&lock1))!=0)
        err_cont(err,"can't unlock lock1 in child handler\n");
    if((err=pthread_mutex_unlock(&lock2))!=0)
        err_cont(err,"can't unlock lock2 in child  handler\n");
}

void *thr_fn(void *arg)
{
    printf("thread started....\n");
    pause();
    return 0;
}
int main(void)
{
    int err ;
    pid_t pid;
    pthread_t tid;
    //atfork作用是使fork之后的锁状态保持一致
    if((err=pthread_atfork(prepare,parent,child))!=0)
    {
        err_exit(err,"can't install fork handlers");
    }
    if((err=pthread_create(&tid,NULL,thr_fn,0))!=0)
    {
        err_exit(err,"can't create thread");
    }
    sleep(2);
    printf("parent about t ofork ...\n");



    if((pid=fork())<0)
        err_quit("fork error");
    else if(pid==0)
        printf("child return from fork \n");
    else 
        printf("parent return from fork\n");
    exit(0);
}

