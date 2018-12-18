#include "apue.h"
static void sig_usr(int); // one handler for both signals

int main(void)
{
	printf("hello\n");
	if (signal(SIGUSR1,sig_usr) == SIG_ERR)
		err_sys("can't catch 1 ");
	if (signal(SIGUSR2,sig_usr) == SIG_ERR)
		err_sys("can't catch 2 ");
	for ( ; ; )
		pause();
}

static void sig_usr(int signo)
{
	printf("conme\n");
	if(signo == SIGUSR1)
		printf("received SIGUSR1,signo=%d\n",signo);
	else if(signo == SIGUSR2)
		printf("received SIGUSR2,signo=%d\n",signo);
	else
		err_dump("received signal %d\n",signo);

}

/*
 amazingtai@AmazingTaideMacBook-Pro  ~/Desktop/OS/c/10_UNIX_Signal   master  ls
a.out   catch.c
 amazingtai@AmazingTaideMacBook-Pro  ~/Desktop/OS/c/10_UNIX_Signal   master  ./a.out &
[1] 6299
hello
 ⚙ amazingtai@AmazingTaideMacBook-Pro  ~/Desktop/OS/c/10_UNIX_Signal   master  kill -USR1 6299
conme
received SIGUSR1
 ⚙ amazingtai@AmazingTaideMacBook-Pro  ~/Desktop/OS/c/10_UNIX_Signal   master  kill -USR2 6299
conme
received SIGUSR2
 ⚙ amazingtai@AmazingTaideMacBook-Pro  ~/Desktop/OS/c/10_UNIX_Signal   master  kill 6299
[1]  + 6299 terminated  ./a.out
 ⚙ amazingtai@AmazingTaideMacBook-Pro  ~/Desktop/OS/c/10_UNIX_Signal   master 
*/