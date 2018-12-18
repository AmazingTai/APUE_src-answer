

#include"apue.h"
int main(void)
{
	pid_t pid;
	if(pid=fork()<0)
	{
		err_sys("fork error");
	}
	else if(pid!=0)
	{
		sleep(2);
		exit(2);
	}
	if(pid=fork()<0)
	{
		err_sys("fork error");
	}
	else if(pid!=0)
	{
		sleep(4);
		abort();
	}
	if(pid=fork()<0)
	{
		err_sys("fork error");
	}
	else if(pid!=0)
	{
		execl("/bin/dd","dd","if=/etc/passwd","of=/dev/null",NULL);//对于dd of 而言是对一个文件块进行扩张，将if对应的文件扩大of对应的大小
		exit(7);//should get here
	}

	if(pid=fork()<0)
	{
		err_sys("fork error");
	}
	else if(pid!=0)
	{
		sleep(8);
		exit(0);
	}
//
	sleep(6);  //4
	kill(getpid(),SIGKILL);
	exit(6);
}
