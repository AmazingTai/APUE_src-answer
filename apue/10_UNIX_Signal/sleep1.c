#include "apue.h"
#include <signal.h>
#include <unistd.h>

static jmp_buf env_alam;

static void sig_alrm(int signo)
{
	longjmp(env_alam,1);
}

unsigned int sleep2(unsigned int seconds)
{
	if(signal(SIGALRM,sig_alrm) == SIG_ERR){
		//err_sys("signal error");
		return (seconds);
	}
	if(setjmp(env_alam) == 0){
		alarm(seconds); //star the timer
		pause();	//next caught signal
	}
	
	return (alarm(0));  //tuen off timer return unslept time

}
