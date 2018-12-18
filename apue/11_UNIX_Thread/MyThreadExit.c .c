

#include "apue.h" 
#include<pthread.h>
struct foo
{
    int a,b,c,d;
};
void printffoo(const char *s,const struct foo *fp)
{
    printf("%s",s);
    printf("structure at 0x%1x\n",(unsigned long)fp);
    printf("foo.a=%d\n",fp->a);
    printf("foo.b=%d\n",fp->b);
    printf("foo.c=%d\n",fp->c);
    printf("foo.d=%d\n",fp->d);
}


void *thr_fn1(void *arg)
{
    struct foo foo ={1,2,3,4};
    printffoo("thread 1:\n",&foo);

    pthread_exit((void*)&foo);
}
void *thr_fn2(void *arg)
{
    printf("thread 2 ID is %lu \n" ,(unsigned long)pthread_self());
    pthread_exit((void *)0);
}


int main(void)
{
    int         err;
    pthread_t   tid1,tid2;
    struct foo *fp; 

    if((err=pthread_create(&tid1,NULL,thr_fn1,NULL))!=0)
        err_exit(err,"can't create pthread 1");
    if((err=pthread_join(tid1,(void*)&fp))!=0)
        err_exit(err,"can't join with thread 1");
    sleep(1);
    printf("parent starting second thread");
    if((err=pthread_create(&tid2,NULL,thr_fn2,NULL))!=0)
        err_exit(err,"can't create pthread 2");
    sleep(1);
    printffoo("parent:\n" ,&fp);
    exit(0);
}

/*
thread 1:
structure at 0x19dfed0
foo.a=1
foo.b=2
foo.c=3
foo.d=4
parent starting second threadthread 2 ID is 123145329442816
parent:
structure at 0xe8419970
foo.a=27131600
foo.b=28672
foo.c=27131904
foo.d=28672
*/
