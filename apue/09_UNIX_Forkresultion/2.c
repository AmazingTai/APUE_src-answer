#include "apue.h"
#include <errno.h>

static void sig_hup(int signo)
{
	printf("SIGHUP received,pid = %ld\n",(long)getpid );

}
static void pr_ids(char * name)
{
	printf("%s: pid = %ld, ppid = %ld , pgrp = %ld, tpgrp = %ld \n",name,(long)getpid(), (long)getppid(),(long)getpgrp(),(long)tcgetpgrp(STDIN_FILENO));
	
	fflush(stdin); //冲刷缓冲区

}

int main()
{
	pid_t  pid;
	char c;
	pr_ids("parent");
	if(pid = fork() <0 )
		err_sys("fork error");
	else if (pid  > 0)
	{
		sleep(5);
	}
	else 
	{
		pr_ids("child");
		//signal(SIGHUP,sig_ids);
		//kill(getpid(),SIGTSTP);
		setsid();
		pr_ids("child");
		if(read(STDIN_FILENO,&c,1)!=1)
			printf("read error %d on contralling TTY\n",errno);
	}

	exit(0);

}
